#include <stdio.h>
#include <string.h>

static u_int32_t hash (const char *string)
{
    u_int32_t ret = 0;
    for(size_t i = 0; string[i]; i++)
    {
        ret += string[i];
    }
    return ret;
}

static struct {
    u_int8_t dir;
    const char *str;
}
dirs[] ={{0,"NORTH"},{1,"EAST"},{2,"SOUTH"},{3,"WEST"}
};

static u_int8_t *get_int(u_int8_t dir)
{
   dir = dir % 4;
    for(size_t i = 0; i<sizeof dirs/sizeof dirs[0];i++){
        if(dirs[i].dir == dir){
            return dirs[i].str;
        }
    }
    return 5;
}

static const char *get_string(u_int8_t dir)
{
   dir = dir % 4;
    for(size_t i = 0; i<sizeof dirs/sizeof dirs[0];i++){
        if(dirs[i].dir == dir){
            return dirs[i].str;
        }
    }
    return "?";
}

static void clamp (int *x,int min, int max)
{
    if(*x < min) *x = min;
    if(*x> max) *x = max;
}

static const char *direction(int *x, int *y, u_int8_t dir)
{
   dir = dir % 4;

   //printf("%i\n",dir,*x,*y);
   switch (dir) {
       case 0: *x = *x + 1; break;
       case 1: *y = *y + 1; break;
       case 2: *x = *x - 1; break;
       case 3: *y = *y - 1; break;
   }
   //clamp (x,0,5);
   //clamp (y,0,5);
}


int main (void)
{
    static char line[1024];
    int x = 0, y = 0, xdir = 0,ydir=0;
    u_int8_t dir=0;
    int newx,newy, facing;

    while(!ferror(stdin)&&!feof(stdin)){
        memset (line,0,sizeof line);
        if(!(fgets(line,sizeof line -1,stdin)))
        continue;

        char *tmp = strchr(line, '\n');
        if(tmp)
            *tmp = 0;

        char *args = strcht(line,' ');
        if(args){
            *args++ = 0;
        }

        switch(hash(line)){
            case 357: scanf(args,"%i %i %s\n", &x, &y,facing);
                    dir = get_int(facing);
                    if(dir>4)
                    break;
                    clamp(&x,0,5);
                    clamp(&y,0,5);
                    break; //place
            case 311: move(&x,&y,dir);
                    clamp(&x,0,5);
                    clamp(&y,0,5);
                    break;//move

            case 299: dir = dir--;
                    break; //left
            case 382: dir = dir++;break; //right
            case 476: printf("Output: %i,%i,%s\n",x,y,get_string(dir));
                      break; //report

        }
        printf("%u\n",dir);
        //dir = dir % 3;
    }


    return 0;

}
