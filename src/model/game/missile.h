/*
	missile management
*/

typedef struct
{
	float angle;
	float pos_x;
	float pos_y;
	float speed;
}missile;

//prototypes
missile create(float pos_x,float pos_y,float speed,float angle);//Angle will be calculated
missile create(float pos_x,float pos_y,float speed,float to_x,float to_y);//Angle will be calculated

void explode(missile *mis); // Might trigger an event in the view
