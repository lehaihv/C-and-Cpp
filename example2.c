#include <stdio.h>
#include <string.h>

struct car
{
    /* data */
    char *maker;
    char *model;
    float price;
    int year;
};

void car_details(struct car *acar);
void change_car_details(struct car *acar, char *maker, char *model, float price, int year);

void main(void)
{
    struct car huyndai10 = {"Huyndai", "I10", 545, 2021};

    //car_details(&huyndai10);
    //huyndai10.year = 2023;
    car_details(&huyndai10);
    change_car_details(&huyndai10, "", "Camry", 231, 2000);
    car_details(&huyndai10);

}

void car_details(struct car *acar)
{
    printf("Make by: %s\n", acar->maker);
    printf("Model: %s\n", acar->model);
    printf("Price: %f\n", acar->price);
    printf("Year: %d\n", acar->year);
}

void change_car_details(struct car *acar, char *newmaker, char *newmodel, float newprice, int newyear)
{
    if (newmaker != "") acar->maker = newmaker;
    if (newmodel != "") acar->model = newmodel;
    if (newprice > 0) acar->price = newprice;
    if (newyear > 0) acar->year = newyear;
}