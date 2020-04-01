/*
	missile management
*/
typedef struct
{
	float angle;
	float pos_x;
	float pos_y;
	float speed;
}*Missile;

//prototypes
Missile create(float pos_x,float pos_y,float speed,float angle);//Angle will be calculated
Missile update_pos_missile(Missile m);
void explode(Missile mis); // Might trigger an event in the view
