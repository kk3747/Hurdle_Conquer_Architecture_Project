#include <stdio.h>

#define JTAG_UART_BASE ((volatile int *)0xFF201000)
volatile int *JTAG_UART_ptr = (int *)0xFF201000;
#define JTAG_UART_CONTROL ((volatile int *)(0xFF201000 + 4))

volatile int *SW_ptr = (volatile int *)0xFF200040; // address of switches

# define GREEN 0x0444
#define WHITE 0xffff

	char cc='S';
	int ii=1;
int lvl=1;
void game_over();

void draw_vert(int x1,int y1,int l, short colour)
{
	int i;
	for (i=0;i<l;i++)
		write_pixel(x1,y1+i,colour);
}
void draw_hori(int x1,int y1,int l, short colour)
{
	int i;
	for(i=0;i<l;i++){
		write_pixel(x1+i,y1,colour);
}}



void draw_line(int x1,int y1,int x2,int y2, short color){
    for(int i = x1;i<=x2;i++){
        for(int j = y1;j<=y2;j++){
            write_pixel(i,j,color);
        }
    }
}


int x , y ;


void write_pixel(int x, int y, short colour)
{
    volatile short *vga_addr = (volatile short *)(0x08000000 + (y << 10) + (x << 1));
    *vga_addr = colour;
}

// short read_pixel(int x, int y) {
//   volatile short vga_addr=(volatile short)(0x08000000 + (y<<10) + (x<<1));
//   return *vga_addr;
// }
void draw_rectangle(int x1, int y1, int x2, int y2, short colour) {
  int x, y;
  // Draw the horizontal lines
  for (x = x1; x <= x2; x++) {
    write_pixel(x, y1, colour);
    write_pixel(x, y2, colour);
  }
  // Draw the vertical lines
  for (y = y1; y <= y2; y++) {
    write_pixel(x1, y, colour);
    write_pixel(x2, y, colour);
  }
}


void spike(int x, int y, short colour)
{
  int i = 0;
  for (i = 0; i < 5; i++)
    draw_line(x + i, y - i, x + 10 - i, y - i, colour);
}

void spike_rev(int x, int y, short colour){
    int i = 0;
  for (i = 0; i < 5; i++)
    draw_line(x + i, y + i, x + 10 - i, y + i, colour);
}

void spiker(int x, int y, short colour)
{
  int i = 0;
  for (i = 0; i < 5; i++)
    draw_hori(x + i, y + i,10-2*i, colour);
}

void flag(int x, int y){
  draw_vert(x,y-10,20,0xffa500);
  draw_vert(x+1,y-10,20,0xffa500);
  //draw_line(x,y,x,y+10,0xdddd);
	//draw_line(x+4,y-10,x+4,y-20,0xdddd);
	//draw_line(x+2,y-10,x+2,y-20,0xdddd);
	//draw_line(x+3,y-10,x+3,y-20,0xdddd);
    
	for(int i = 0;i<10;i++){
		draw_vert(x+2+i,y-10,10,0xf800);
	}
	
	/*draw_vert(x+2,y-10,10,0x0440);
	draw_vert(x+3,y-10,10,0x0440);
	draw_vert(x+4,y-10,10,0x0440);
	draw_vert(x+5,y-10,10,0x0440);
	draw_vert(x+6,y-10,10,0x0440);
	draw_vert(x+7,y-10,10,0x0440);
	draw_vert(x+8,y-10,10,0x0440);
	draw_vert(x+9,y-10,10,0x0440);*/
    //draw_line(x,y,x,y,0xdddd);
	//draw_line(x,y,x,y,0xdddd);
	//draw_line(x,y,x,y,0xdddd);
	//draw_line(x,y,x,y,0xdddd);
}

void flag_rev(int x, int y){
   draw_vert(x,y-10,20,0xffa500);
  draw_vert(x+1,y-10,20,0xffa500);
	for(int i = 0;i<10;i++){
		draw_vert(x-1-i,y,10,0xf800);
	}
	
}

void spikes(int x, int y, short colour)
{
  spike(x, y, colour);
  spike(x + 10, y, colour);
  spike(x + 20, y, colour);
	draw_hori(x,y,30,GREEN);
}
void spikesr(int x, int y, short colour)
{
  spiker(x, y, colour);
  spiker(x + 10, y, colour);
  spiker(x + 20, y, colour);
	draw_hori(x,y,30,GREEN);
}
void boundary()
{
  draw_rectangle(30, 40, 290, 210, 0x0ff0);
	draw_rectangle(25, 35, 295, 215, 0x0ff0);
}
void level1()
{
  boundary();
  draw_rectangle(70, 170, 120, 210, 0x0ff0);
  draw_rectangle(150, 140, 190, 210, 0x0ff0);
  draw_rectangle(220, 110, 290, 210, 0x0ff0);
// portal(270,110,WHITE);  
	spike_rev(90,40,WHITE);spike_rev(90,40,WHITE);spike_rev(100,40,WHITE);
	//spike_rev(120,40,WHITE);
	//spike_rev(130,40,WHITE);
	//spike_rev(140,40,WHITE);
	
	
	flag(260,100);
	
	
	spike_rev(155,40,WHITE);
	spike_rev(165,40,WHITE);
	spike_rev(260,40,WHITE);
	spike_rev(270,40,WHITE);
	spike_rev(250,40,WHITE);
	spike_rev(240,40,WHITE);
	spike_rev(230,40,WHITE);
	//spike_rev(225,40,WHITE);
	//spike_rev(160,40,WHITE);
	//spike_rev(180,40,WHITE);
spikes(120, 210, WHITE);
  spikes(190, 210, WHITE);
  draw_line(70, 210, 120, 210, 0x0000);
  draw_line(150, 210, 190, 210, 0x0000);
  draw_line(220, 210, 289, 210, 0x0000);
  draw_rectangle(290, 110, 290, 210, 0x0000);
	
}


void level2()
{
  boundary();

	//UPPER AREA
	draw_line(30,120,90,120,GREEN);
	draw_vert(90,120,10,GREEN);
	draw_line(90,130,120,130,GREEN);
	draw_vert(120,120,10,GREEN);
	spikes(90,130,WHITE);

	
	spike_rev(40,40,WHITE);spike_rev(50,40,WHITE);spike_rev(60,40,WHITE);
	spike_rev(130,40,WHITE);spike_rev(140,40,WHITE);
	spike_rev(240,40,WHITE);spike_rev(250,40,WHITE);
	spike_rev(230,40,WHITE);spike_rev(260,40,WHITE);
	spike_rev(40,40,WHITE);spike_rev(50,40,WHITE);spike_rev(60,40,WHITE);
	spike_rev(210,130,WHITE);spike_rev(220,130,WHITE);
	
	spike_rev(150,130,WHITE);spike_rev(140,130,WHITE);spike_rev(130,130,WHITE);
	draw_line(120,120,170,120,GREEN);
	draw_vert(170,120,10,GREEN);
	spikes(170,130,WHITE);
	draw_vert(200,120,10,GREEN);
	draw_hori(200,120,40,GREEN);
	draw_vert(240,120,10,GREEN);
	draw_hori(210,130,30,GREEN);
	draw_vert(210,130,10,GREEN);
	draw_hori(160,140,50,GREEN);
	draw_vert(160,130,10,GREEN);
	draw_hori(130,130,30,GREEN);
	draw_vert(130,130,10,GREEN);
	draw_hori(80,140,50,GREEN);
	draw_vert(80,130,10,GREEN);
	draw_hori(30,130,50,GREEN);
	draw_vert(30,121,9,0x0000);
	
	
	//LOWER AREA
	draw_vert(100,140,50,GREEN);
	draw_hori(100,190,60,GREEN);
	draw_vert(160,190,10,GREEN);
	draw_hori(160,200,50,GREEN);
	draw_vert(210,190,10,GREEN);
	draw_hori(210,190,80,GREEN);
	draw_vert(290,181,9,0x0000);
	draw_hori(101,140,9,0x0000);
	draw_vert(110,140,40,GREEN);
	draw_hori(110,180,60,GREEN);
	draw_vert(170,180,10,GREEN);
	draw_hori(170,190,30,GREEN);
	spikes(170,190,WHITE);
	draw_vert(200,180,10,GREEN);
	draw_hori(200,180,90,GREEN);
	// portal(130,180,WHITE);
	flag_rev(115,150);
	//spike_rev(40,40,WHITE);spike_rev(50,40,WHITE);spike_rev(60,40,WHITE);
	
}

void level3()
{
	boundary();
	draw_hori(30,180,120,GREEN);
	draw_vert(110,150,10,GREEN);
	draw_hori(110,150,50,GREEN);
	draw_vert(160,150,30,GREEN);
	draw_hori(151,190,9,0x0000);
	spikes(160,180,WHITE);
	draw_hori(30,180,120,GREEN);
	draw_vert(150,160,20,GREEN);
	draw_hori(110,160,40,GREEN);
	draw_vert(190,150,30,GREEN);
	draw_hori(190,150,40,GREEN);
	draw_vert(230,120,30,GREEN);
	draw_hori(230,120,30,GREEN);
	draw_vert(260,120,30,GREEN);
	//draw_hori(260,140,30,GREEN);
	//draw_vert(290,141,9,0);
	draw_vert(290,141,9,GREEN);
	draw_vert(290,141,9,GREEN);
	// portal(275,140,WHITE);
	flag(205,170);
	draw_hori(250,150,10,GREEN);
	draw_vert(250,130,20,GREEN);
	draw_hori(240,130,10,GREEN);
	draw_vert(240,130,30,GREEN);
	draw_hori(200,160,40,GREEN);
	draw_vert(200,160,20,GREEN);
	draw_hori(200,180,90,GREEN);
	draw_vert(30,181,9,0);
	draw_hori(30,190,260,GREEN);
	draw_vert(290,181,9,0);	
	//spike_rev();
	spike_rev(40,40,WHITE);spike_rev(50,40,WHITE);spike_rev(60,40,WHITE);
	spike_rev(115,40,WHITE);spike_rev(125,40,WHITE);spike_rev(135,40,WHITE);
	spike_rev(195,40,WHITE);
	spike_rev(245,40,WHITE);spike_rev(255,40,WHITE);spike_rev(265,40,WHITE);spike_rev(275,40,WHITE);
}

void level4()
{
	boundary();
	draw_hori(30,85,65,GREEN);
	draw_hori(145,85,30,GREEN);
	draw_hori(225,85,25,GREEN);
	draw_hori(95,75,50,GREEN);
	draw_hori(175,75,50,GREEN);
	
	draw_hori(30,95,75,GREEN);
	draw_hori(135,95,50,GREEN);
	draw_hori(215,95,25,GREEN);
	
	draw_vert(95,75,10,GREEN);
	draw_vert(145,75,10,GREEN);
	draw_vert(105,85,10,GREEN);	
	draw_vert(135,85,10,GREEN);
	
	spikesr(105,85,WHITE);
	spikesr(185,85,WHITE);
	
	draw_vert(175,75,10,GREEN);
	draw_vert(225,75,10,GREEN);
	draw_vert(185,85,10,GREEN);	
	draw_vert(215,85,10,GREEN);
	
	draw_vert(30,86,9,0);
	draw_vert(290,86,9,0);

	draw_vert(240,95,60,GREEN);
	draw_vert(250,85,80,GREEN);
	draw_vert(290,85,10,GREEN);
	
	draw_hori(30,165,65,GREEN);
	draw_hori(145,165,30,GREEN);
	draw_hori(225,165,25,GREEN);
	draw_hori(95,175,50,GREEN);
	draw_hori(175,175,50,GREEN);
	
	draw_hori(80,155,25,GREEN);
	draw_vert(80,155,10,GREEN);
	draw_hori(135,155,50,GREEN);
	draw_hori(215,155,25,GREEN);
	draw_hori(30,165,50,0);
	
	draw_vert(95,165,10,GREEN);
	draw_vert(145,165,10,GREEN);
	draw_vert(105,155,10,GREEN);	
	draw_vert(135,155,10,GREEN);
	
	draw_vert(175,165,10,GREEN);
	draw_vert(225,165,10,GREEN);
	draw_vert(185,155,10,GREEN);	
	draw_vert(215,155,10,GREEN);
	
	spikes(105,165,WHITE);
	spikes(185,165,WHITE);
	//spikesr(105,165,WHITE);
	spikesr(145,165,WHITE);
	spike_rev(85,165,WHITE);
	// portal(60,155,WHITE);
	spikes(100,210,WHITE);
	spike(190,210,WHITE);
	spike(200,210,WHITE);
	
	
	spike_rev(38,40,WHITE);
	spike_rev(48,40,WHITE);
	spike_rev(58,40,WHITE);
	spike_rev(68,40,WHITE);
	
	spike_rev(99,40,WHITE);
	spike_rev(109,40,WHITE);
	spike_rev(119,40,WHITE);
	spike_rev(129,40,WHITE);
	
	spike_rev(190,40,WHITE);
	spike_rev(200,40,WHITE);
	
	spike(225,85,WHITE);
	spike(235,85,WHITE);
	
	
	spike_rev(265,40,WHITE);
	spike_rev(275,40,WHITE);
	
	draw_vert(30,156,9,0);
	draw_vert(290,156,9,0);
	
	draw_hori(95,115,50,GREEN);
	draw_hori(95,125,50,GREEN);
	draw_vert(95,115,10,GREEN);
	draw_vert(145,115,10,GREEN);
	
	
	draw_hori(180,115,40,GREEN);
	draw_hori(180,125,40,GREEN);
	draw_vert(180,115,10,GREEN);
	draw_vert(220,115,10,GREEN);
	flag(235,145);
	
}



void clear_screen()
{
    int x, y;
    for (x = 0; x < 320; x++)
    {
        for (y = 0; y < 240; y++)
        {
            write_pixel(x, y, 0);
        }
    }
}
// key bindings start
char get_jtag(volatile int *JTAG_UART_ptr)
{
    int data;
    data = *(JTAG_UART_ptr);
    if (data & 0x00008000) // check RVALID
        return ((char)data & 0xFF);
    else
        return ('\0');
}

// print user text to console
void put_jtag(volatile int *JTAG_UART_ptr, char c)
{
    int control;
    control = *(JTAG_UART_ptr + 1); // read control reg
    if (control & 0xFFFF0000)
    {
        *(JTAG_UART_ptr) = c;
    }
}
short read_pixel(int x, int y)
{
    volatile short *vga_addr = (volatile short *)(0x08000000 + (y << 10) + (x << 1));
    return *vga_addr;
}
void line4exm(int x, int y)
{

    for(x=x; x < 100; x++)
    {
        write_pixel(x, y, 0x07e0);
    }
}

void box(int x, int y)
{
    int i, j;
    for (i = (x - 5); i <= (x + 5); i++)
    {
        for (j = (y - 5); j <= (y + 5); j++)
        {
            write_pixel(i, j, 0x07e0);
        }
    }
}
void clear_square(int x, int y)
{
    int i, j;
    for (i = (x - 5); i <= (x + 5); i++)
    {
        for (j = (y - 5); j <= (y + 5); j++)
        {
            write_pixel(i, j, 0x0000);
        }
    }
}
int is_white(int x, int y) {
    short color = read_pixel(x, y);
    int red = (color >> 11) & 0x1F;    // Extract red component (bits 11-15)
    int green = (color >> 5) & 0x3F;   // Extract green component (bits 5-10)
    int blue = color & 0x1F;           // Extract blue component (bits 0-4)
    return (red == 31 && green == 63 && blue == 31);   // Return true if all components are maximum
}

int is_red(int x, int y) {
    short color = read_pixel(x, y);
    int red = (color >> 11) & 0x1F;    // Extract red component (bits 11-15)
    int green = (color >> 5) & 0x3F;   // Extract green component (bits 5-10)
    int blue = color & 0x1F;           // Extract blue component (bits 0-4)
    return (red == 31 && green == 0 && blue == 0);   // Return true if red is maximum and green and blue are minimum
}

int is_orange(int x, int y) {
    short color = read_pixel(x, y);
    int red = (color >> 11) & 0x1F;    // Extract red component (bits 11-15)
    int green = (color >> 5) & 0x3F;   // Extract green component (bits 5-10)
    int blue = color & 0x1F;           // Extract blue component (bits 0-4)
    return (red == 31 && green == 20 && blue == 0);   // Return true if all components match orange
}
void delay(int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		asm volatile("nop");
	}
}


void move(int x, int y)
{
    char c;
    volatile int *JTAG_UART_ptr = (int *)JTAG_UART_BASE;
    while (1)
    {
		
		for(int i = -7;i<8;i++){
            for(int j = -7;j<8;j++){
                short p =read_pixel(x,y);
                if(is_white(x+i,y+j)){
                    cc='S';
                    game_over();
                    //cc='S'
                    
                    break;
                }
		    }
		}
		
		
		for(int i = -10;i<11;i++){
            for(int j = -10;j<11;j++){
                short p = read_pixel(x,y);
                if(is_red(x+i,y+j)||is_orange(x+i,y+j)){
                    lvl+=1;
                    cc='S';
                    gameplay();
                    break;
                }
            }
		}
		

        printf("%s" , " inside move = " ) ;
        printf( "%d %d  # " , x , y ) ;
        if( read_pixel(x-7,y+7)==0  ) printf("%s \n" , "left corner " ) ;
        if( read_pixel(x,y+7)==0  ) printf("%s \n " , "down corner " ) ;
        if( read_pixel(x+7,y+7)==0  ) printf("%s \n" , "right corner " ) ;

		if( *SW_ptr == 2 && read_pixel(x,y+7)==0 && read_pixel(x-7,y+7)==0 && read_pixel(x+7,y+7)==0){
			cc='S';
            clear_square(x, y);
            printf( "%d %d  # " , x , y ) ;
            if (read_pixel(x, y + 7) == 0 && read_pixel(x+7,y+7)==0 && read_pixel(x-7,y+7)==0)
            {
				// while(read_pixel(x, y + 7) == 0x0000 && read_pixel(x+7,y+7)==0 && read_pixel(x-7,y+7)==0){
               
                y += 1;
				// }
                printf( "inner %d %d  # " , x , y ) ;
                box(x, y );
                // break;
            }
            else
            {
                box(x, y);
            }
		}

        // if(cc=='W' && read_pixel(x,y-7)==0 && read_pixel(x-7,y-7)==0 && read_pixel(x+7,y-7)==0){
		// 	int o = 0; 
		//  cc='W';
		// 	clear_square(x,y);
        //     read_pixel(x, y);
        //     if (read_pixel(x, y - 7) == 0x0000 &&read_pixel(x+7,y-7)==0 && read_pixel(x-7,y-7)==0)
        //     { 	while(read_pixel(x, y - 7) == 0x0000 &&read_pixel(x+7,y-7)==0 && read_pixel(x-7,y-7)==0){
                
        //         y -= 1;
		// 		}box(x, y);
        //     }
        //     else
        //     {
        //         box(x, y);
        //     }
		// }

        c = get_jtag(JTAG_UART_ptr);
        printf( "%d " , c ) ;

        if ( *SW_ptr == 1 ) // move right
        {
            printf( "%s" , "right = " ) ;

            // delay(10000000);
			clear_square(x, y);
            if (read_pixel(x+7,y)==0 && read_pixel(x+7,y+6)==0 && read_pixel(x+7,y-6)==0)
            {
                box(x + 1, y);
                x += 1;
            }
            else
            {
                box(x + 0, y);
                x -= 0;
            }

            delay(100);
        }

        else if ( *SW_ptr == 8 ) // move left
        {
            printf( "%s" , "left = " ) ;
            clear_square(x, y);
            if (read_pixel(x-7,y)==0 && read_pixel(x-7,y+6)==0 && read_pixel(x-7,y-6)==0)
            {
                box(x - 1, y);
                x -= 1;
            }
            else
            {
                box(x + 0, y);
                x -= 0;
            }

            delay(100);
        }

        else if ( *SW_ptr== 4 ) // move up
        {int o = 0; 
		 cc='W';
         printf( "%s" , "up = " ) ;
			clear_square(x,y);
            read_pixel(x, y);
            if (read_pixel(x, y - 7) == 0 &&read_pixel(x+7,y-7)==0 && read_pixel(x-7,y-7)==0)
            { 	//while(read_pixel(x, y - 7) == 0x0000 &&read_pixel(x+7,y-7)==0 && read_pixel(x-7,y-7)==0){
                
                y -= 1;
				//}
                box(x, y);
            }
            else
            {
                box(x, y);
            }
            delay(100);
        }

        else if ( *SW_ptr == 2 ) // move down
        {
            if( y + 1 < 200 )  {
			cc='S';
            printf( "%s" , "down = " ) ;
            clear_square(x, y);
            if (read_pixel(x, y + 7) == 0x0000 && read_pixel(x+7,y+7)==0 && read_pixel(x-7,y+7)==0)
            {
				// while(read_pixel(x, y + 7) == 0x0000 && read_pixel(x+7,y+7)==0 && read_pixel(x-7,y+7)==0){
               
                //     y += 1;
                    printf ("y = %d " , y ) ;
                //     delay(1000);
				// } 
                y++;
                printf ("y = %d " , y ) ;
                box(x, y );
            }
            else
            {
                y++;
                box(x, y);
            }

            }
            // delay(1000000);
        }else if ( *SW_ptr == 12 ) // move left max
        {
            
            clear_square(x, y);
            if (read_pixel(x-7, y) == 0 && read_pixel(x-7,y+7)==0 && read_pixel(x-7,y-7)==0)
            {
				//while(read_pixel(x-7, y) == 0x0000 && read_pixel(x-7,y+7)==0 && read_pixel(x-7,y-7)==0){
               
                x -= 1;
				//} 
                box(x, y );
                break;
            }
            else
            {
                box(x, y);
            }
            delay(1000);
        }else if ( *SW_ptr== 3 ) // move right max
        {
            //delay(1000000);
            clear_square(x, y);
            if (read_pixel(x+7, y) == 0 && read_pixel(x+7,y+7)==0 && read_pixel(x+7,y-7)==0)
            {
				// while(read_pixel(x+7, y ) == 0x0000 && read_pixel(x+7,y+7)==0 && read_pixel(x+7,y-7)==0){
               
                x += 1;
				//} 
                box(x, y );
            }
            else
            {
                box(x, y);
            }
            delay(1000);
        }
		else if ( *SW_ptr == 16 ) // refresh
        {
		
           gameplay();
        }
        
    }
}

void game_over(){
clear_screen();
	boundary();
draw_vert(100,75,48,GREEN);
draw_hori(100,75,25,GREEN);
draw_hori(100,95,20,GREEN);
draw_vert(101,75,48,GREEN);
draw_hori(100,76,25,GREEN);
draw_hori(100,96,20,GREEN);
	
draw_hori(130,75,10,GREEN);
draw_hori(130,76,10,GREEN);
draw_vert(140,75,48,GREEN);
draw_vert(141,75,48,GREEN);
draw_hori(130,123,20,GREEN);
draw_hori(130,122,20,GREEN);
	
draw_vert(160,75,48,GREEN);
draw_vert(161,75,48,GREEN);
draw_hori(160,75,20,GREEN);
draw_hori(160,76,20,GREEN);
draw_vert(200,75,48,GREEN);
draw_vert(201,75,48,GREEN);
draw_hori(180,123,20,GREEN);
draw_hori(180,122,20,GREEN);
draw_vert(180,75,48,GREEN);
draw_vert(181,75,48,GREEN);
	
}

void gameplay(){
clear_screen();
if(lvl==1){
	int x = 50;
	int y = 50;
	clear_screen();
	box(x,y);
	level1();
	
	move(x,y);
} 
else
	if(lvl==2){
	int x = 50;
	int y = 70;
	box(x,y);
	clear_screen();
	level2();
	
	move(x,y);
}else
	if(lvl==3){
	int x = 70;
	int y = 90;
	box(x,y);
	clear_screen();
	level3();
	
	move(x,y);
}else
	if(lvl==4){
	int x = 50;
	int y = 60;
	box(x,y);
	clear_screen();
	level4();
	
	move(x,y);
}else if(lvl==5){

boundary();
draw_vert(120,75,50,GREEN);
	draw_vert(121,75,50,GREEN);
	draw_hori(120,75,25,GREEN);
	draw_hori(120,76,25,GREEN);
	draw_vert(145,75,15,GREEN);
	draw_vert(146,75,15,GREEN);
	draw_hori(120,125,25,GREEN);
	draw_hori(120,126,25,GREEN);
	draw_vert(145,100,50,GREEN);
	draw_vert(146,101,50,GREEN);
	draw_hori(135,100,15,GREEN);
	draw_hori(136,101,15,GREEN);
	
	draw_vert(170,75,50,GREEN);
	draw_vert(171,75,50,GREEN);
	draw_hori(170,75,25,GREEN);
	draw_hori(170,76,25,GREEN);
	draw_vert(195,75,15,GREEN);
	draw_vert(196,75,15,GREEN);
	draw_hori(170,125,25,GREEN);
	draw_hori(170,126,25,GREEN);
	draw_vert(195,100,50,GREEN);
	draw_vert(196,101,50,GREEN);
	draw_hori(185,100,15,GREEN);
	draw_hori(186,101,15,GREEN);
}
}

int main()
{
    
    gameplay();
}