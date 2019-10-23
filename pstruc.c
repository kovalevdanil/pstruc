#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <dirent.h>

static char spaces[128];

int print_structure(const char *dir_path, int spaces_num)
{
	DIR *dir = opendir(dir_path);
	if (dir == NULL)
	{
		return -1;
	}

	struct dirent *d;
	const char next_dir_path[256];

	while ((d = readdir(dir)) != NULL)
	{
		if (d->d_name[0] == '.')
			continue;

		int is_dir = d -> d_type == 4;

		printf("%.*s%s\n", spaces_num * 2 ,spaces, d->d_name);

		snprintf(next_dir_path, 256, "%s/%s", dir_path, d->d_name);
		if (is_dir)
			print_structure(next_dir_path, spaces_num + 1);
	}

	closedir(dir);

	return 0;
}

int main(int argc, char **argv)
{
	char target_dir[256];

	if (argc == 1)
		getcwd(target_dir, 256);
	else if (argc == 2)
		strcpy(target_dir, argv[1]);
	else
		return -1;

	memset(spaces, ' ', 128);
	if (print_structure(target_dir, 0) == -1)
	{
		perror("opendir");
		return -1;
	}

	return 0;
}
