typedef struct slave_message {
	short length;	/* msg length */
	char *buf;	/* pointer to msg data */
	unsigned char (*rec_proc)(BYTE Chan_ID,UBYTE *buffer); /*process Function*/
} slave_msg;
typedef struct slave_params_list
{
	int Chan;
	OS_EVENT *event;
}slave_params_list_t;
extern void MTx(slave_msg *msg);
extern void Tx(UBYTE chanid,slave_msg *msg);

