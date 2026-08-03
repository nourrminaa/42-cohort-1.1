/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmina <nmina@student.42beirut.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:21:46 by nmina             #+#    #+#             */
/*   Updated: 2026/01/26 11:27:24 by nmina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int	*arr;
	int	size;
	int	capacity;
}	t_stack;

typedef enum e_strategy
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_strategy;

typedef struct s_cmd
{
	int			*arr;
	int			n;
	t_strategy	strat;
	int			bench;
}	t_cmd;

t_cmd		parse_arguments(int argc, char **argv);
int			*parse_numbers(char **argv, int argc, int start);
int			count_numbers(char **argv, int argc, int start);
char		*join_arguments(char **argv, int argc, int start);
char		**ft_split(char *str, char c);
void		free_split(char **arr);
int			validate_and_count(char **split);
int			*fill_array(char **split, int n);
int			ft_strlen(const char *s);
char		*ft_strdup_local(const char *s);
char		*ft_strjoin_space(char *s1, char *s2);
int			get_start(char **argv, int argc);
t_strategy	get_strategy(char **argv, int argc);
int			has_bench_flag(char **argv, int argc);
int			ft_strcmp(char *s1, char *s2);
int			is_allowed_flag(char *s);
int			check_non_digit(char *s);
int			check_all_args(char **args, int start, int end);
int			check_duplicates_int(int *arr, int n);
void		show_error(void);
void		show_error_free(int *arr, char **split);
int			atoi_arg(char *str, int *arr, char **split);
void		swap(t_stack *stack);
void		push(t_stack *from, t_stack *to);
void		rotate(t_stack *stack);
void		reverse_rotate(t_stack *stack);
void		free_stack(t_stack *stack);
void		stack_pop(t_stack *stack);
int			check_sort_order(t_stack *stack);
int			get_top(t_stack *stack);
t_stack		copy_stack(t_stack *original);
void		sa(t_stack *a, int *op_count);
void		sb(t_stack *b, int *op_count);
void		pa(t_stack *a, t_stack *b, int *op_count);
void		pb(t_stack *a, t_stack *b, int *op_count);
void		ra(t_stack *a, int *op_count);
void		rb(t_stack *b, int *op_count);
void		rra(t_stack *a, int *op_count);
void		rrb(t_stack *b, int *op_count);
void		ss(t_stack *a, t_stack *b, int *op_count);
void		rr(t_stack *a, t_stack *b, int *op_count);
void		rrr(t_stack *a, t_stack *b, int *op_count);
int			get_max(t_stack *stack);
int			get_max_position(t_stack *stack);
int			get_min_position(t_stack *a);
int			shortest_rotation_direction(t_stack *stack, int target_pos);
void		push_back(t_stack *a, t_stack *b, int *op_count);
int			get_max_bits(int max_index);
int			*get_sorted_copy(const t_stack *a);
void		index_with_sorted(t_stack *a, const int *sorted);
void		swap_int(int *a, int *b);
void		index_stack(t_stack *a);
void		sort_insertion(t_stack **a, t_stack **b, int *op_count);
void		sort_bucket(t_stack **a, t_stack **b, int *op_count);
void		sort_quick(t_stack **a, t_stack **b, int *op_count);
void		sort_adaptive(t_stack **a, t_stack **b, int *op_count);
double		compute_disorder(t_stack stack);
void		sort_two(t_stack *a, int *op_count);
void		sort_three(t_stack *a, int *op_count);
void		sort_small(t_stack *a, t_stack *b, int *op_count);
int			partition(int *arr, int low, int high);
void		quick_sort(int *arr, int low, int high);
void		radix_index_stack(t_stack *a);
void		print_bench(int *op_count, t_strategy strat, double disorder);
void		put_nbr_fd(int n, int fd);
int			ft_isspace(char c);

#endif
