import Foundation

// Enum for media type
enum MediaType: String, Codable {
    case photo = "Photo"
    case video = "Video"
    case text = "Text"
}

// Struct for User Profile
struct UserProfile: Codable {
    let username: String
    let profileImageURL: String
}

// Class for Feed Post
class FeedPost: Codable {
    let user: UserProfile
    let mediaType: MediaType
    let content: String
    let timestamp: Date
    var likes: Int

    init(user: UserProfile, mediaType: MediaType, content: String, timestamp: Date, likes: Int) {
        self.user = user
        self.mediaType = mediaType
        self.content = content
        self.timestamp = timestamp
        self.likes = likes
    }

    // Helper function: Format likes (e.g., 413000 -> 413.0k)
    func formattedLikes() -> String {
        if likes >= 1_000_000 {
            return String(format: "%.1fM", Double(likes) / 1_000_000)
        } else if likes >= 1_000 {
            return String(format: "%.1fk", Double(likes) / 1_000)
        } else {
            return "\(likes)"
        }
    }


    // Helper function: Format date
    func formattedDate() -> String {
        let formatter = DateFormatter()
        formatter.dateFormat = "dd.MM.yyyy"
        return formatter.string(from: timestamp)
    }

    // Print post details
    func display() {
        print("Profile: \(user.username)\t| Media: \(mediaType.rawValue)\t| Date: \(formattedDate())\t| Likes: \(formattedLikes())")
    }
}

// Struct to match JSON format for decoding
struct FeedPostJSON: Codable {
    let username: String
    let profileImageURL: String
    let mediaType: String
    let content: String
    let timestamp: String
    let likes: Int
}

// Function to read JSON from file
func readJSONFromFile(filename: String) -> Data? {
    let fileURL = URL(fileURLWithPath: filename)

    do {
        let data = try Data(contentsOf: fileURL)
        return data
    } catch {
        print("Error reading file: \(error)")
        return nil
    }
}

// Function to parse JSON
func parseFeed(from jsonData: Data) -> [FeedPost] {
    let decoder = JSONDecoder()
    let formatter = DateFormatter()
    formatter.dateFormat = "yyyy-MM-dd"
    decoder.dateDecodingStrategy = .formatted(formatter)

    do {
        let decodedPosts = try decoder.decode([FeedPostJSON].self, from: jsonData)
        return decodedPosts.map {
            FeedPost(
                user: UserProfile(username: $0.username, profileImageURL: $0.profileImageURL),
                mediaType: MediaType(rawValue: $0.mediaType) ?? .text,
                content: $0.content,
                timestamp: formatter.date(from: $0.timestamp) ?? Date(),
                likes: $0.likes
            )
        }
    } catch {
        print("Error decoding JSON: \(error)")
        return []
    }
}

// Load and parse JSON from file
if let jsonData = readJSONFromFile(filename: "data.json") {
    let jsonFeed = parseFeed(from: jsonData)
    
    // Print parsed feed posts
    for post in jsonFeed {
        post.display()
    }
} else {
    print("Failed to load JSON data.")
}
