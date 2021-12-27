/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:45:03 by bahn              #+#    #+#             */
/*   Updated: 2021/12/27 12:15:05 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://ahngbeom-bahn.notion.site/1487214afdfb44d4aa01ad6e0391da2e

static	char	*redirection_finder(char *dest, char **src, char **find_redirection)
{
	char	*find_ptr;	// 리다이렉션 탐색 결과를 저장할 변수
	char	*forefront;	// 가장 전방에 있는 리다이렉션
	int		i;

	forefront = NULL;
	find_ptr = NULL;
	i = -1;
	while (src[++i] != NULL)
	{
		find_ptr = ft_strnstr(dest, src[i], ft_strlen(dest));
		// 만약 현재 find_ptr이 이전에 찾은 find_ptr(forefront)보다 전방에 위치한다면
		if (find_ptr != NULL && (forefront == NULL || forefront > find_ptr))
		{
			forefront = find_ptr;
			*find_redirection = src[i];
		}
	}
	return (forefront);
}

void	ft_split_command(t_list **list, char *input, char **redirect)
{
	char		*ptr; // input(readline())에서 각 명령어의 시작 주소
	t_command 	*cmd; // 각 명령어들의 데이터를 저장할 변수
	char		*temp;
	char		*find_redirection; // redirect(g_data.arr_redirect)에서 존재하는 리다이렉션을 저장하기 위한 변수

	ptr = input;
	while (ptr != NULL && *ptr != '\0')
	{
		find_redirection = NULL;

		// 각 명령어들의 데이터를 저장할 공간 확보
		cmd = ft_calloc(sizeof(t_command), 1);

		// g_data.command 연결 리스트에 추가
		if (list == NULL)
			*list = ft_lstnew(cmd);
		else
			ft_lstadd_back(list, ft_lstnew(cmd));

		// 해당 명령어가 빌트인 명령어인지, 외부 실행 파일에 의한 명령어인지 구분하기위한 변수 초기화
		cmd->bulit_in_flag = 0;
		
		// 리다이렉션 배열을 탐색하며 해당되는 리다이렉션이 있는지 검사
		temp = redirection_finder(ptr, redirect, &find_redirection);
		
		// redirection_finder 함수를 통해 찾은 리다이렉션 저장
		cmd->redirect = find_redirection;

		// 리다이렉션이 존재한다면
		if (temp != NULL)
		{
			// (리다이렉션의 위치 - 1) 까지 문자열 자르기 => 명령어 구문 추출
			cmd->argv = ft_split(ft_substr(ptr, 0, ft_strlen(ptr) - ft_strlen(temp)), ' ');
			// 다음 명령어의 위치로 ptr 이동
			ptr = ft_strtrim(temp + ft_strlen(find_redirection) + 1, " ");
		}
		// 리다이렉션이 존재하지않다면
		else
		{
			cmd->argv = ft_split(ptr, ' ');
			break ;
		}
	}
	if (ptr == input)
		free(input);
	else
		free(ptr);
}
