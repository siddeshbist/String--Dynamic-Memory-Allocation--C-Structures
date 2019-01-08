//Siddesh Bist
//LO5
//400072076
//Lab 3
//Q2

#include <stdio.h>
#include <stdlib.h>

typedef struct{  //structure of type student
        int ID;
        char *fn;
        char *ln;
        int P1;
        int P2;
        float grade;
        } student;

student **create_class_list(char *filename,int *sizePtr){

    int i=0,n;
    FILE *input_file=fopen(filename,"r");//open file for reading
    fscanf(input_file,"%d",sizePtr);//find the number of students by reading the first integer
    n=*sizePtr;   //n is assigned the value of the integer at the top of the file, or the number of students

    student **listofstudents= calloc(n,sizeof(n));//dynamically allocating memory to store the double pointer and initializing it at zero
    student *info= (calloc(n,sizeof(student)));//dynamically allocating memory for an array of pointers to type student and initializing them at zero

    while(i<n)
    {
        int id;
        listofstudents[i]=(student*)calloc(1,sizeof(student)); //initialize all the pointers to 0
        fscanf(input_file,"%d",&id);//the first int read in the file is stored as id
        info[i].ID = id; //store the value of id read from file in member ID of structure
        info[i].fn=malloc(15*sizeof(char));//allocate memory to store first name
        fscanf(input_file,"%s",info[i].fn); //the first string read is stored in member of fn of the structure
        info[i].ln=malloc(15*sizeof(char));//allocate memory to store the last name
        fscanf(input_file,"%s",info[i].ln);//the next string read is stored in member ln of the structure
        //printf("%d %s %s\n",info[i].ID,info[i].fn,info[i].ln);
        listofstudents[i]=&info[i];//each pointer of type student is stored in the double pointer
        i++;
    }
    fclose(input_file);//close file
    return listofstudents;//return double pointer which contains an array of pointers
}

void print_list(student**list,int size)
{
    int i;
    for(i=0;i<size;i++){
        printf("%d,",list[i]->ID); //prints the value that the list index points too
        printf("%s,",list[i]->fn);
        printf("%s,",list[i]->ln);
        printf("%d,",list[i]->P1);
        printf("%d,",list[i]->P2);
        printf("%f\n",list[i]->grade);
    }
    return list;

}

int find (int idNo,student**list,int size)
{
    int i=0;
    while(i<size)
    {
       if(list[i]->ID==idNo)//if the id of the member matches the id entered then return index
       {
           return i;
       }
       i++;
    }

    return -1; //if the id entered does not match the id stored in the structure then -1 is returned
}

void input_grades(char*filename,student**list,int size)
{
    FILE*input_file=fopen(filename,"r");//open file
    int i=0;
    int tempindex;
    while(i<size)
    {
        int tempid,grade1,grade2;
        fscanf(input_file,"%d",&tempid);//reads the first int in the file and stores it in tempid
        tempindex=find(tempid,list,size); //use the find function to determine position of student in list
        fscanf(input_file,"%d",&grade1);//reads the second int in the file and stores it in grade 1
        list[tempindex]->P1=grade1; //the member P1 is updated to the value of grade 1
        fscanf(input_file,"%d",&grade2);// reads the next int in the file and stores it in grade 2
        list[tempindex]->P2=grade2;//the member P2 is updated to the value of grade 2
        i++;
    }
    fclose(input_file);
    return list;
}

void compute_final_course_grades(student**list,int size)
{
    int i=0;
    while(i<size)
    {
        list[i]->grade=((list[i]->P1)+(list[i]->P2))/2.0; //find the average of the project 1 and project 2 grade
        i++;
    }
}

void output_final_course_grades(char*outputinfo,student**list,int size)
{
    FILE*output_file=fopen(outputinfo,"w");//open file to write
    fprintf(output_file,"%d\n",size);//the value of size is written to the file
    int i=0;
    while(i<size)
    {
        fprintf(output_file,"%d ",list[i]->ID); //the value stored in ID is written to the file
        fprintf(output_file,"%f\n",list[i]->grade); //the value stored in grade is written to the file
        i++;

    }
    fclose(output_file);
}


void withdraw(int idNo, student**list,int*sizePtr)
{
    int count=0;//indication that idNo has been found
    int index=0; //stores index of idNo and initialized at -1 because index can be 0
    int i;
    int j =0;
    for(i=0;i<*sizePtr;i++)//loops through the entire list
    {

        if(idNo==list[i]->ID) //if the id entered matches the id stored in the structure
        {
            list[i]=calloc(*sizePtr,sizeof(student));//all members of the structure that have that ID are initialized to zero
            free(list[i]);//memory deallocated for that matched id as well members of that structure
            count=1;//update to 1, indicating match has been found


            for (j=i;j<(*sizePtr-1);j++) //moves all the pointer element to the right by 1
                {
                list[j]=list[j+1];
                }
        }

    }


    if(count==0)//if count is not updated then id entered is not on list and message printed
    {
        printf("None of the students ID'S match with the ID entered\n");
    }
    else
        {
        --*sizePtr; //size of array is reduced by 1 as information of 1 student is removed

         }


}

void destroy_list(student**list,int*sizePtr)
{
  int i=0;
  while (i<*sizePtr)
  {
      list[i]=calloc(*sizePtr,sizeof(student));//allocate memory for each student type and initialize to zero
      free(list[i]); //every pointer element of the array has it memory deallocated
      i++;
  }
  free(list); //the double pointer array has its memory deallocated
  *sizePtr=0;    //size of the array of pointers is set to 0
  i++;
}


int main(int argc, char** argv){

    int n,no;
    student **Data= create_class_list("input_file.txt",&n);
    input_grades("grades_file.txt",Data,n);
    compute_final_course_grades(Data,n);
    output_final_course_grades("outputinfo.txt",Data,n);
    withdraw(8000,Data,&n);
    withdraw(1200,Data,&n);
    withdraw(9000,Data,&n);
    destroy_list(Data,&n);
    //no=find (9000,Data,n);
    //printf("%d",no);
    print_list(Data,n); //use printlist function to print student information
    return 0;
}

