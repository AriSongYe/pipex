### Subject  개요

`Pipex`에 사용되는 함수를 먼저 보고 사용해보면 과제의 흐름이 보입니다.

이번 과제에서는

우리가 `쉘`에서 `CLI`를 통해 사용하는 ‘|’ `pipe` 를 직접 구현하는 과제입니다.

Mandatory Part는 단순히 `Pipe` 하나만을

Bonus Part는 `Multi Pipe`와 `here_doc`을 구현하는게 목표 입니다.

# Code Flow Chart
![image](https://github.com/AriSongYe/pipex/assets/82326075/c06f60c2-a37b-4244-95a5-c344055d258b)


# Mandatory

### Checking argument & infile

```c
int	check_file(t_info **info, char **argv)
{
	if ((*info)->argc != 5)
	{
		write(2, "Error : check your arguments\n", 30);
		exit(1);
	}
	if (access(argv[1], R_OK))
		perror_exit("Error :Check input file");

// arguments가 개수에 맞게 들어왔는지 확인한다.
// access 함수를 통해 파일의 존재 유무와 읽을 수 있는 권한 확인을 한다.
```

### Parsing path

```c
char	**parsing_path(char **envp)
{
	char	**path;
	char	*temp;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			break ;
		(*envp)++;
	}
	temp = ft_strdup(*envp + 5);
	path = ft_split(temp, ':');
	free(temp);
	return (path);
}

// main에 대한 인수 중에 환경변수를 갖고 있는 envp를 가져와서 PATH를 찾아 parsing 합니다.
```

### Checking cmd

```c
char	**valid_cmd(char *cmd, char **path)
{
	char	**cmd_info;
	char	*temp;
	int		i;
	int		sign;

	i = 0;
	sign = 0;
	cmd_info = ft_split(cmd, ' ');
	if (!access(cmd_info[0], F_OK))
		return (cmd_info);
// 경로를 바로 넣어준 경우 처리
	while (path[i])
	{
		temp = join_path(cmd_info[0], path[i]);
		if (!access (temp, F_OK))
		{
			sign = 1;
			break ;
		}
		if (path [1 + i++] != NULL)
			free(temp);
	}
	free(cmd_info[0]);
	cmd_info[0] = temp;
	cmd_error(sign);
	return (cmd_info);
}

// 들어온 cmd를 access 함수를 통해 존재하는 명령어인지 확인합니다.
// 유효하지 않은 명령어이더라도 pipe 명령어 자체가 병렬적으로 진행되기 때문에 프로그램을 종료하지 않습니다.
```

### pipe

```c
void	child_exec(t_info **info, char **argv, int fd[2], pid_t pid)
{
	int		in_fd;

	if (pid == 0 && (*info)->i == 0)
	{
		close(fd[0]);
		in_fd = open(argv[1], O_RDONLY);
		dup2(in_fd, 0);
		dup2(fd[1], 1);
		execve((*info)->cmd_info[0], (*info)->cmd_info, NULL);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve((*info)->cmd_info[0], (*info)->cmd_info, NULL);
	}
}

void	parent_exec(t_info **info, char **argv, int fd[2], pid_t pid)
{
	int		o;
	char	*temp;

	if (pid > 0 && (*info)->i == (*info)->argc - 4)
	{
		close(fd[1]);
		o = open(argv[(*info)->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (o == -1)
			perror_exit("Error : open file Error");
		temp = read_fd(fd[0]);
		write(o, temp, ft_strlen(temp));
		if (temp && temp[0] != '\0')
			free(temp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, WNOHANG);
	}
}

void	pipe_line(t_info **info, char **argv)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		perror_exit("Error : pipe function");
	pid = fork();
	if (pid == -1)
		perror_exit("Error : fork function");
	child_exec(info, argv, fd, pid);
	parent_exec(info, argv, fd, pid);
}

// 시작, 자식프로세스에서 dup2 를 통해 standard input을 infile의 file descriptor로 변경
// dup2 를 통해 standard output을 pipe의 write 부분으로 변경, 부모 프로세스에게 전달
// 부모 프로세스에서 standard input을 pipe의 read 로 변경 하여 다음 동작 실행 -> 반복 
// 마지막, outfile에 write 한다.
```

# Bonus

## Multi Pipe

- mandatory를 잘 구성했다면 while 문을 통해 반복문으로 돌리면 된다.
- arguments 개수 제한을 5개가 아닌 5개 미만으로 바꿀 것.

## Here Documents

1. here_doc이 인자로 들어왔는지 체크한다.
2. 임시 파일을 생성한다
3. 임시 파일을 open하고 write를 while 문을 통해 받는다.
4. multi pipe를 실행한다.
5. unlink 함수를 통해 임시 파일을 지워준다.
