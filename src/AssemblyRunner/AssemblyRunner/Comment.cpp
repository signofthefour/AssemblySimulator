#include "Comment.h"


bool isComment(char * line)
{
	while (*(line) == ' ') line++;
	return *(line) == '#';
}
