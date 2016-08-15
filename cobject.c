// C面向对象（封装继承多态）：面向对象从来都是思想，而不是语言。
#include <stdio.h>
#include<math.h>

#include<stdlib.h>


struct shape;
struct shape_ops   // 接口
{
    /*函数指针 返回几何体的面积*/
    float (*so_area)(struct shape*); 
    /*返回几何体的周长*/
    int (*so_perimeter)(struct shape*);
};

struct shape 	// 父类
{
    int s_type;
    char *s_name;
    struct shape_ops* s_ops; /*虚接口，所有子类必须实现*/
};

float shape_area(struct shape* s)  /*求形状面积*/
{
	// 通过结构体赋值，将子类的函数指针设置进来
    return s->s_ops->so_area(s);  
}
int shape_perimeter(struct shape* s) /*求周长*/
{
    return s->s_ops->so_perimeter(s);
}

/*三角形 */
struct triangle
{
	// 继承shape的s_type,s_name属性
    struct shape t_base;
    int t_side_a;
    int t_side_b;
    int t_side_c;
};

float triangle_area(struct shape* s)  /*三角形面积，用海伦公式*/
{
    struct triangle* t=(struct triangle*)s;
    int a=t->t_side_a;
    int b=t->t_side_b;
    int c=t->t_side_c;
    float p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

int triangle_perimeter(struct shape* s)  /*三角形周长*/
{
    struct triangle* t=(struct triangle*)s;
    int a=t->t_side_a;
    int b=t->t_side_b;
    int c=t->t_side_c;
    return a+b+c;
}

struct shape_ops triangle_ops=    /*对父类虚接口的实现，使用“=”对结构体成员进行初始化("triangle_ops=")*/
{
	// 对结构体成员(函数指针)的赋值
    triangle_area,
    triangle_perimeter,
};

struct triangle* triangle_create(int a,int b,int c)  /*创建三角形*/
{
    struct triangle* ret=(struct triangle*)malloc(sizeof (*ret));
	ret->t_base.s_type = 1;
    ret->t_base.s_name="triangle";
    ret->t_base.s_ops=&triangle_ops;   // 结构体赋值
    ret->t_side_a=a;
    ret->t_side_b=b;
    ret->t_side_c=c;
    return ret;
}

/*矩形 */
struct rectangle
{
	// 继承shape的s_type,s_name属性
    struct shape r_base;
    int r_width;
    int r_height;
};

float rectangle_area(struct shape* s)  /*矩形面积*/
{
    struct rectangle* r=(struct rectangle*)s;
    return r->r_width*r->r_height;
}

int rectangle_perimeter(struct shape* s)/*矩形周长*/
{
    struct rectangle* r=(struct rectangle*)s;
    return (r->r_width+r->r_height)*2;
}

struct shape_ops rectangle_ops=      /*对父类虚接口的实现，使用“=”对结构体成员进行初始化("rectangle_ops=")*/
{
    rectangle_area,
    rectangle_perimeter,
};

struct rectangle* rectangle_create(int width, int height)  /*创建矩形*/
{
    struct rectangle* ret=(struct rectangle*)malloc(sizeof(*ret));
	ret->r_base.s_type = 2;
    ret->r_base.s_name="rectangle";
    ret->r_base.s_ops=&rectangle_ops;
    ret->r_height=height;
    ret->r_width=width;
    return ret;
}

int main()
{
    struct shape* s[4];
	// 使用父类指针指向子类对象
    s[0]=triangle_create(5,5,4);
    s[1]=triangle_create(3,4,5);
    s[2]=rectangle_create(10,12);
    s[3]=rectangle_create(5,8);

    int i=0;
    for(i=0;i<4;i++)
    {
		// 多态
        float area=shape_area(s[i]);    
        int perimeter=shape_perimeter(s[i]);
		 // 继承
        char* name=s[i]->s_name;
		int type = s[i]->s_type;
        printf("type:%d, name:%s ,area:%.2f ,perimeter:%d\n",type, name,area,perimeter);
    }
    return 0;
}

/*
output:

type:1, name:triangle ,area:9.17 ,perimeter:14
type:1, name:triangle ,area:6.00 ,perimeter:12
type:2, name:rectangle ,area:120.00 ,perimeter:44
type:2, name:rectangle ,area:40.00 ,perimeter:26

--------------------------------
Process exited after 0.01184 seconds with return value 0
请按任意键继续. . .
*/

