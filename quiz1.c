#include <stdio.h>
#include <math.h>

double x(int a, int b);
double y(int a, int b);
double z(int a, int b);

int main(void) 
{
    int value1;
    int value2; 
    printf("\n");
    printf("----  Finding unknown triple (x,y and z)   ----\n");
    printf("Enter values of a and b, separated by space>\n");
    scanf("%d %d", &value1, &value2);
    printf("The unknown triple set is: \n");
    printf("x=%.2f \n",x(value1,value2));
    printf("y=%.2f \n",y(value1,value2));
    printf("z=%.2f \n",z(value1,value2));

    return 0;
}

double x(int a, int b) {
    double answer;
    answer = pow(a,2) - pow(b,2);
    return answer;
}
double y(int a, int b){
    double answer;
    answer = 2 * a * b;
    return answer;

}

double z(int a, int b) {
    double answer;
    answer = pow(a,2) + pow(b,2);
    return answer;
}