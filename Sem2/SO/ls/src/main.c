#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct
{
	struct dirent* entry;
	char full_path[1024];
} dirent_with_path;



void print_file_info(const char *path, const struct stat *file_stat) {
    char permissions[12];
    strcpy(permissions, "----------.");

    // File type
    if (S_ISDIR(file_stat->st_mode)) permissions[0] = 'd';
    if (S_ISLNK(file_stat->st_mode)) permissions[0] = 'l';

    // Owner permissions
    if (file_stat->st_mode & S_IRUSR) permissions[1] = 'r';
    if (file_stat->st_mode & S_IWUSR) permissions[2] = 'w';
    if (file_stat->st_mode & S_IXUSR) permissions[3] = 'x';

    // Group permissions
    if (file_stat->st_mode & S_IRGRP) permissions[4] = 'r';
    if (file_stat->st_mode & S_IWGRP) permissions[5] = 'w';
    if (file_stat->st_mode & S_IXGRP) permissions[6] = 'x';

    // Other permissions
    if (file_stat->st_mode & S_IROTH) permissions[7] = 'r';
    if (file_stat->st_mode & S_IWOTH) permissions[8] = 'w';
    if (file_stat->st_mode & S_IXOTH) permissions[9] = 'x';

    struct passwd *pw = getpwuid(file_stat->st_uid);
    struct group  *gr = getgrgid(file_stat->st_gid);
    char time_buf[80];
    strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", localtime(&file_stat->st_mtime));

    printf("%s %lu %s %s %2ld %s %s\n",
        permissions,
        file_stat->st_nlink,
        pw->pw_name,
        gr->gr_name,
        file_stat->st_size,
        time_buf,
        path);
}

bool recursiveDir(char* current_path, int depth) {
    if (depth > 10) {
        printf("\n---too far away!---\n");
        return false;
    }

    DIR* current_dir = opendir(current_path);
    struct dirent *file;
    struct stat file_stat;

    if (current_dir == NULL) {
        return false;
    }

    char** files = NULL;
    size_t file_count = 0;
    char** dirs = NULL;
    size_t dir_count = 0;

    while ((file = readdir(current_dir)) != NULL) {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            continue;
        }

        char new_path[2048];
        snprintf(new_path, sizeof(new_path), "%s/%s", current_path, file->d_name);

        if (stat(new_path, &file_stat) == 0 && S_ISDIR(file_stat.st_mode)) {
            dirs = realloc(dirs, sizeof(char*) * (dir_count + 1));
            dirs[dir_count] = strdup(new_path);
            dir_count++;
        } else {
            files = realloc(files, sizeof(char*) * (file_count + 1));
            files[file_count] = strdup(new_path);
            file_count++;
        }
    }

    for (size_t i = 0; i < file_count; i++) {
        printf("%*s", depth * 4, "");

        if (i == file_count - 1) {
            if (dir_count == 0) {
                printf("└");
            }
            else {
                printf("├");
            }
        }
        else {
            printf("├");
        }
        printf("───");

        printf("%s\n", strrchr(files[i], '/') + 1);
        free(files[i]);
    }
    free(files);

    for (size_t i = 0; i < dir_count; i++) {
        printf("%*s", depth * 4, "");

        printf("└───");

        printf("%s\n", strrchr(dirs[i], '/') + 1);;
        recursiveDir(dirs[i], depth + 1);
        free(dirs[i]);
    }
    free(dirs);

    closedir(current_dir);
    return true;
}

int main(int argc, char* argv[])
{
    bool normal_mode = true;
    bool long_mode = false;
    bool Recursive_mode = false;
    bool all_mode = false;
    bool almost_all_mode = false;
    bool one_line_mode = false;
    bool size_mode = false;

    bool time_sort = false;

    DIR* current_dir;
    struct dirent *file;
    struct stat file_stat;

    char current_path_file[2048];
    char *current_path = (argc == 1) ? "." : argv[argc - 1]; 

    struct dirent** namelist;
	int n = scandir(current_path, &namelist, NULL, alphasort);
	dirent_with_path* entries = (dirent_with_path*)malloc(n * sizeof(dirent_with_path));

	for(int i = 0; i < n; i++)
	{
		entries[i].entry = namelist[i];
		snprintf(entries[i].full_path, sizeof(entries[i].full_path), "%s/%s", current_path, namelist[i]->d_name);
	}
    
    if (argc == 1) {
        current_dir = opendir(".");   
    }
    else {
        current_dir = opendir(argv[argc - 1]);
        if (argc > 2) {
            normal_mode = false;

            if(strcmp(argv[1], "-l") == 0) {long_mode = true;}
            else if (strcmp(argv[1], "-R") == 0) {Recursive_mode = true;}
            else if (strcmp(argv[1], "-a") == 0) {all_mode = true;}
            else if (strcmp(argv[1], "-A") == 0) {almost_all_mode = true;}
            else if (strcmp(argv[1], "-1") == 0) {one_line_mode = true;}
            else if (strcmp(argv[1], "-s") == 0) {size_mode = true;}
            else {normal_mode = true;}
        }
    }

    if (normal_mode) {
        for(int i = 0; i < n; i++)
        {
            file = entries[i].entry;

            if (file->d_name[0] == '.') {
                continue;
            }

            printf("%s  ", file->d_name);
        }
        printf("\n");
    }
    else if (Recursive_mode)
    {
        recursiveDir(argv[argc - 1], 1);
    }
    else if (long_mode) {
        for(int i = 0; i < n; i++) {
            file = entries[i].entry;

            if (file->d_name[0] == '.') {
                continue;
            }

            snprintf(current_path_file, sizeof(current_path_file), "%s/%s", current_path, file->d_name);
            if (stat(current_path_file, &file_stat) == 0) {
                print_file_info(file->d_name, &file_stat);
            }
        }
    }
    else if (all_mode) {
        for(int i = 0; i < n; i++)
        {
            file = entries[i].entry;

            printf("%s  ", file->d_name);
        }
        printf("\n");
    }
    else if (almost_all_mode) {
        for(int i = 0; i < n; i++)
        {
            file = entries[i].entry;

            if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
                continue;
            }
            printf("%s  ", file->d_name);
        }
        printf("\n");
    }
    else if (one_line_mode) {
        for(int i = 0; i < n; i++)
        {
            file = entries[i].entry;

            if (file->d_name[0] == '.') {
                continue;
            }

            printf("%s\n", file->d_name);
        }
    }
    else if (size_mode) {
        int total_size = 0;
        int file_size;

        for(int i = 0; i < n; i++)
        {
            file = entries[i].entry;

            if (file->d_name[0] == '.') {
                continue;
            }

            if (stat(file->d_name, &file_stat) == 0) {
                file_size = file_stat.st_blocks / 2; //st_block's block size is 512, which is 2 times lover than ls -s block size
            }
            else {
                file_size = 0;
            }

            printf("%d %s\n", file_size, file->d_name);
            total_size += file_size;
        }
        printf("total %d blocks\n", total_size);
    }
    
    
    free(entries);
    closedir(current_dir);
}