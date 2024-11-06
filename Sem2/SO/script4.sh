while getopts hvi: OPT; do
    case ${OPT} in
        h) help
        ;;
        v) ./script3.sh
        ;;
        i) PLIK=${OPTARG}
        echo 
        ;;
    esac
done