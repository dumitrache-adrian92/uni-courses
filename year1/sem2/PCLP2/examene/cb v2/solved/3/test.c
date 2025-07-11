#include <stdio.h>

void show_message(unsigned int param_1,void *param_2);
unsigned int check(char *param_1,char *param_2);
void reveal_passwd(void *param_1);
void print(char *param_1);	

int main(void)
{
	// TODO: b)
	reveal_passwd("heard");
  	// TODO: c)
	show_message(19228, "yorkshire terrier");
	return 0;
}
