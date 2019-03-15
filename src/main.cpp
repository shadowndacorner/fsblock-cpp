int g_Verbosity = 0;
char *path = 0;
int blocking = 1;
int recursive = 1;

#include "watch.h"
#include <FileWatcher/FileWatcher.h>
#include <thread>

int poll(FW::SingleThreadedPollingFileWatcher& m_Watcher, FW::FileWatcherEvent& ev, FW::WatchID& watchid)
{
    m_Watcher.update();
    while(m_Watcher.poll(ev))
    {
		switch(ev.action)
		{
		case FW::Actions::Add:
			printf("Create");
			break;
		case FW::Actions::Delete:
			printf("Delete");
			break;
		case FW::Actions::Modified:
			printf("Modified");
			break;
		}
		printf(": %s\n", ev.filename.c_str());
		if (blocking)
			return 1;
        
    }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(50ms);
    return 0;
}

int main(int argc, char** argv)
{
	int c;
	while ((c = getopt(argc, argv, "hbp:nv")) != -1)
	{
		switch (c)
		{
		case 'v':
			g_Verbosity=1;
			break;
		case 'b':
			blocking = 0;
			break;
		case 'p':
			path = optarg;
			break;
		case 'n':
			recursive = 0;
			break;
		case 'h':
			printf("Filesystem Watcher Utility by Ian Diaz\n");
			printf("\t Options:\n");
			printf("\t\t -h: Prints this help message\n");
			printf("\t\t -p <path string>: Specifies the directory to watch.  Uses cwd by default.\n");
			printf("\t\t -b: Blocks the program until a change has been made in the specified directory\n");
			printf("\t\t -n: Specifies that the watch should be non-recursive\n");
			printf("\t\t -v: Verbose mode\n");
			return 0;
		case '?':
			if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr,
						"Unknown option character `\\x%x'.\n",
						optopt);
			return 1;
		default:
			return -2;
		}
	}
    
	if (!path)
	{
		fprintf(stderr, "Error: No path specified.  Use -h to show help.\n");
		return -1;
	}

    FW::SingleThreadedPollingFileWatcher m_Watcher;
    auto watchid = m_Watcher.addWatch(path, recursive == 1 ? true : false);

    FW::FileWatcherEvent ev;
    printf("Watching path %s\n", path);
    
    int res;
    while(true)
    {
        if (res = poll(m_Watcher, ev, watchid))
        {
            return res;
        }
    }

    return 0;
}