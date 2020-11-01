#include "../public/Utils.h"

bool Utils::GenerateCache() {
    std::cout << "Looking for: " << Utils::GetCacheFilePath() << std::endl;

    Poco::File FileCache ( Utils::GetCacheFilePath() );

    if ( !FileCache.exists() ) {
        // file does not exist

        try {
            FileCache.createFile();
        } catch ( Poco::FileException ex ) {
            cout << ex.displayText() << endl;
        }

        cout << "Generating Structure" << endl;

        Utils::GenerateStructure();

        return true;
    }

    cout << "File already exist" << endl;

    return false;
}

std::string Utils::GetCacheFilePath() {

    Poco::Path configFile = Poco::Path ( Poco::Path::configHome() ).append ( Poco::Path ( "Quester/.generated" ) );

    try {
        //ensures directory exist
        Poco::File ( Poco::Path ( Poco::Path::configHome() ).append ( Poco::Path ( "Quester/" ) ) ).createDirectory();
    } catch ( Poco::FileException ex ) {
        cout << ex.displayText() << endl;
    }


    return configFile.toString();
}

void Utils::GenerateStructure() {
    Poco::Path QuestMainFilePath = Poco::Path ( Poco::Path::dataHome() ).append ( Poco::Path ( "Quester/Quests/Base.json" ) );

    auto QuestFolder = Poco::File ( QuestMainFilePath );
    if ( !QuestFolder.exists() ) {
        try {
            //ensures directory exist
            QuestFolder.createDirectories();
            cout << "Created Path: " << QuestMainFilePath.toString() << endl;
        } catch ( Poco::FileException ex ) {
            cout << ex.displayText() << endl;
        }
    }
}

std::string Utils::GetEssentialFile ( FileKind Kind ) {
    Poco::Path QuesterDataPath = Poco::Path ( Poco::Path::dataHome() );

    switch ( Kind ) {
    case FileKind::Cache:
        return Utils::GetCacheFilePath();
        break;
    case FileKind::Quests:
        return QuesterDataPath.append ( Poco::Path ( "Quester/Quests/Base.json" ) ).toString();
        break;
    case FileKind::DefaultWorlds:
        return Poco::Path::current();
        break;
    case FileKind::Swap:
        return "";
        break;
    }

    return "";
}

std::string Utils::GetDefaultWorldsAsList ( std::string Context ) {
    Poco::Path DefaultWorldsPath = Poco::Path ( Context )
                                   .parent()
                                   .append ( "/Public/Default/Worlds.json" );

    std::tuple<Poco::File, bool> t = GetFileFrom ( DefaultWorldsPath );

    // if file exists
    try {
        string buffer;
        string JSONString;
        Poco::FileInputStream fis ( DefaultWorldsPath.toString(), std::ios::out );
        while ( getline ( fis, buffer ) ) {
            cout << buffer << '\n';
            
            JSONString += buffer;
        }
        
        
        
    } catch ( Poco::FileNotFoundException ex ) {
        cout << ex.displayText() << endl;
    }

    return Utils::GetEssentialFile ( FileKind::DefaultWorlds );
}

std::tuple<Poco::File, bool> Utils::GetFileFrom ( std::string FilePath ) {
    Poco::File f ( FilePath );
    return std::tuple<Poco::File, bool> {f, f.exists() };
}
std::tuple<Poco::File, bool> Utils::GetFileFrom ( Poco::File FilePath ) {
    Poco::File f ( FilePath );
    return std::tuple<Poco::File, bool> {f, f.exists() };
}


// Windows Only
void Utils::OpenConsole() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    int outHandle, errHandle, inHandle;
    FILE* outFile, * errFile, * inFile;
    AllocConsole();
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo ( GetStdHandle ( STD_OUTPUT_HANDLE ), &coninfo );
    coninfo.dwSize.Y = 9999;
    SetConsoleScreenBufferSize ( GetStdHandle ( STD_OUTPUT_HANDLE ), coninfo.dwSize );

    outHandle = _open_osfhandle ( ( long ) GetStdHandle ( STD_OUTPUT_HANDLE ), _O_TEXT );
    errHandle = _open_osfhandle ( ( long ) GetStdHandle ( STD_ERROR_HANDLE ), _O_TEXT );
    inHandle = _open_osfhandle ( ( long ) GetStdHandle ( STD_INPUT_HANDLE ), _O_TEXT );

    outFile = _fdopen ( outHandle, "w" );
    errFile = _fdopen ( errHandle, "w" );
    inFile = _fdopen ( inHandle, "r" );

    *stdout = *outFile;
    *stderr = *errFile;
    *stdin = *inFile;

    setvbuf ( stdout, NULL, _IONBF, 0 );
    setvbuf ( stderr, NULL, _IONBF, 0 );
    setvbuf ( stdin, NULL, _IONBF, 0 );

    std::ios::sync_with_stdio();

    freopen ( "CONOUT$", "w", stdout );
#endif
}
