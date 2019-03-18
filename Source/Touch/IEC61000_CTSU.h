/* H/W include header */
/*#include "iodefine.h"*/
#include "r_mpc.h"
#include "r_dtc.h"
#include "r_ctsu.h"
#include "r_cgc.h"

/* S/W include header */
#include "r_cg_userdefine.h"
#include "r_touch_API.h"
#include "r_touch.h"
#include "r_serial_control.h"

extern uint8_t	method;
extern uint16_t drift_reset_permission[SELF_KEY_NUM];
extern uint16_t Filter_ref[SELF_KEY_NUM];
extern uint8_t	 Drift_Permission[SELF_KEY_NUM];

extern void NoiseInCheck( void );
extern uint16_t Touch_LPF(uint16_t Ncount,uint8_t loop);
extern void Touch_Drift_Permission(uint16_t Ncount,uint8_t loop);
extern void TOUCH_CTSU_Reset(void);

#define TOUCH_IEC61000				//Enable IEC61000 countermeasure
//#define TOUCH_IEC61000_LPF		//Enable LPF
#define FILTER_LIMIT	150
#define TOUCH_LPF_COEFFICIENT	(0.1f)      //LPF coefficient,range:(0~1)
