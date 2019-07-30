#include <stdio.h>
#include <conio.h>
#include <windows.h>
//#include<semaphore.h>



struct vehicle
{
 int num ;
 int row ;
 int col ;
  int type ;
} ;



void display( ) ;
void wait ( struct vehicle * ) ;
struct vehicle * add ( int, int, int, int ) ;
void del ( struct vehicle * ) ;
void getfreerowcol ( int, int * ) ;
void getrcbyinfo ( int, int, int * ) ;
void show( ) ;
int info[4][10] ;
int vehiclecount ;
int fourwheelercount ;
int twowheelercount;

int main( )
{
 int choice, type, number, row = 0, col = 0 ;
 int i, tarr[2] ;
 int finish = 1 ;


 struct vehicle *fourwheeler[2][10] ;
 struct vehicle *twowheeler[2][10] ;

  system ( "cls" ) ;


 while ( finish )
 {
    system ( "cls" ) ;

   printf ( "\n vehicle Parking\n" ) ;
  printf ( "1. Arrival\n " ) ;
  printf ( "2. Total no  of vehicle\n" ) ;
  printf ( "3. Total no. of fourwheelers parked\n" ) ;
  printf ( "4. Total no. of twowheelers parked\n" ) ;
  printf ( "5. Display order in which vehicles are parked\n" ) ;
 printf ( "6. Departure of vehicle\n" ) ;
  printf ( "7. Exit\n" ) ;
  scanf ( "%d", &choice ) ;

   switch ( choice )
  {
   case 1 :
          system ( "cls" ) ;
      printf ( "\nAdd: \n" ) ;

          type = 0 ;

          /* check for vehicle type */
          while ( type != 1 && type != 2)
          {
       printf ( "Enter vehicle type (1 for fourwheeler / 2 for twowheeler ): \n" ) ;
            scanf ( "%d", &type ) ;
           if ( type != 1&& type != 2 )
        printf ( "\nInvalid vehicle type.\n" ) ;
          }

       printf ( "Enter vehicle number: " ) ;
      scanf ( "%d", &number ) ;

       /* add fourwheelers' data */
      if ( type == 1|| type == 2 )
      {
       getfreerowcol ( type, tarr ) ;

        if ( tarr[0] != -1 && tarr[1] != -1 )
       {
        row = tarr[0] ;
        col = tarr[1] ;

              if ( type == 1)
                fourwheeler[row][col] =  add ( type, number, row, col ) ;
              else
         twowheeler[row - 2][col] = add ( type, number, row, col ) ; ;
            }
       else
            {
              if ( type == 2 )
                printf ( "\nNo parking slot free to park a fourwheeler\n" ) ;
              else
                printf ( "\nNo parking slot free to park a twowheeler\n" ) ;
            }
          }
      else
      {
            printf ( "Invalid type\n" ) ;
       break ;
          }

          printf ( "\nPress any key to continue..." ) ;
          getch( ) ;
      break ;

      case 2 :
          system ( "cls" ) ;
      printf ( "Total vehicles parked: %d\n", vehiclecount ) ;
          printf ( "\nPress any key to continue..." ) ;
          getch( ) ;
      break ;

    case 3 :
          system ( "cls" ) ;
      printf ( "Total fourwheelers parked: %d\n", fourwheelercount ) ;
          printf ( "\nPress any key to continue..." ) ;
          getch( ) ;
      break ;

    case 4 :
          system ( "cls" ) ;
      printf ( "Total twowheelers parked: %d\n", twowheelercount ) ;
          printf ( "\nPress any key to continue..." ) ;
          getch( ) ;
      break ;

    case 5 :
          //system ( "cls" ) ;
      printf ( "Display\n" ) ;
      display( ) ;
          printf ( "\nPress any key to continue..." ) ;
          getch( ) ;
      break ;


            case  6 :


                printf ( "Departure\n" ) ;

                type = 0 ;

                /* check for vehicle type */
while ( type != 1 && type != 2)
                {
                    printf ( "Enter vehicle type (1 for fourwheeler / 2 for twowheeler ): \n" ) ;
                    scanf ( "%d", &type ) ;
                    if ( type != 1 && type != 2 )
                        printf ( "\nInvalid vehicle type.\n" ) ;
                }
                printf ( "Enter number: "  ) ;
                scanf ( "%d", &number ) ;

                if ( type == 1|| type == 2)
                {
                    getrcbyinfo ( type, number, tarr ) ;
                    if ( tarr[0] != -1 && tarr[1] != -1 )
                    {
                        col = tarr [1] ;

                        /* if the vehicle is fourwheeler */
if ( type == 1 )
                        {
                            row = tarr [0] ;
                            del ( fourwheeler [row][col] ) ;
                            for ( i = col ; i < 9 ; i++ )
                            {
                                fourwheeler[row][i] = fourwheeler[row][i + 1] ;
                                wait ( fourwheeler[row][i] ) ;
                            }
                            free ( fourwheeler[row][i] ) ;
                            fourwheeler[row][i] = NULL ;
                        }
                        /* if a vehicle is twowheeler */
else
                        {
                            row = tarr[0] - 2 ;
                            if ( ! ( row < 0 ) )
                            {
                                del ( twowheeler[row][col] ) ;
                                for ( i = col ; i < 9 ; i++ )
                                {
                                    twowheeler[row][i] = twowheeler[row][i + 1] ;
                                    wait ( twowheeler[row][col] ) ;
                                }
                                twowheeler[row][i] = NULL ;
                            }
                        }
                    }
                    else
                    {
                        if ( type == 1 )
                            printf ( "\nInvalid fourwheeler number, or a fourwheeler with such number has not been parked here.\n" ) ;
                        else
                            printf ( "\nInvalid twowheeler number, or a twowheeler with such number has not been parked here.\n" ) ;
                    }
                }

                printf ( "\nPress any key to continue..." ) ;
                getch( ) ;
                break ;



    case 7 :
          system ( "cls" ) ;
          for ( row = 0 ; row < 2 ; row++ )
          {
            for ( col = 0 ; col < 10 ; col++ )
            {
              if ( fourwheeler[row][col] -> num != 0 )
                free ( fourwheeler[row][col] ) ;
              if ( twowheeler[row][col] -> num != 0 )
         free ( twowheeler[row+2][col] ) ;
            }
          }
      finish = 0 ;
      break ;
    }
 }
  return 0 ;
}


void wait ( struct vehicle *v )
{
 v -> col = v -> col - 1 ;
}


struct vehicle * add (int t,int num,int row,int col)
{
    struct vehicle *v ;

    v = ( struct vehicle * ) malloc ( sizeof ( struct vehicle ) ) ;

    v -> type = t ;
    v -> row = row ;
    v -> col = col ;

    if ( t == 1 )
      fourwheelercount++ ;
    else
     twowheelercount++ ;

    vehiclecount++ ;
   info[row][col] = num ;

    return v ;
}


void del ( struct vehicle *v )
{
  int c ;

  for ( c = v -> col ; c < 9 ; c++ )
   info[v -> row][c] = info[v -> row][c+1] ;

  info[v -> row][c] = 0 ;

  if ( v -> type == 1 )
    fourwheelercount-- ;
  else
    twowheelercount-- ;

  vehiclecount-- ;
}


void getfreerowcol ( int type, int *arr )
{
  int r, c, fromrow = 0, torow = 2 ;

  if ( type == 2 )
  {
    fromrow += 2 ;
    torow += 2 ;
  }

  for ( r = fromrow ; r < torow ; r++ )
 {
  for ( c = 0 ; c < 10 ; c++ )
  {
   if ( info[r][c] == 0 )
   {
    arr[0] = r ;
    arr[1] = c ;
        return ;
   }
  }
 }

  if ( r == 2 || r == 4 )
 {
    arr[0] = -1 ;
    arr[1] = -1 ;
  }
}


void getrcbyinfo ( int type, int num, int *arr )
{
  int r, c, fromrow = 0, torow = 2 ;

  if ( type == 2 )
 {
    fromrow += 2 ;
    torow += 2 ;
 }

  for ( r = fromrow ; r < torow ; r++ )
 {
  for ( c = 0 ; c < 10 ; c++ )
  {
   if ( info[r][c] == num )
   {
    arr[0] = r ;
    arr[1] = c ;
        return ;
   }
  }
 }

  if ( r == 2 || r == 4 )
 {
  arr[0] = -1 ;
  arr[1] = -1 ;
 }
}

void display( )
{
  int r, c ;

  printf ( "fourwheelers ->\n" ) ;

  for ( r = 0 ; r < 4 ; r++ )
  {
    if ( r == 2 )
    printf ( "twowheelers ->\n" ) ;

    for ( c = 0 ; c < 10 ; c++ )
      printf ( "%d\t", info[r][c] ) ;
    printf ( "\n" ) ;
 }
}

