#include "IEC61000_CTSU.h"

#include "r_touch.h"
#include "r_touch_API.h"

uint16_t drift_reset_permission[SELF_KEY_NUM];
uint16_t count_overflow = 0;
uint16_t Filter_ref[SELF_KEY_NUM];
uint8_t	 Drift_Permission[SELF_KEY_NUM];

void NoiseInCheck( void )
{
	uint8_t loop;
	uint8_t multi_on_counter;

    for (loop = 0,multi_on_counter = 0; loop < SELF_KEY_NUM; loop++)
    {
		//if(*(g_key_info[method].delta+loop)>(*(g_key_info[method].user_thr+loop)-500))
		if(*(g_key_info[0].delta+loop)>((*(g_key_info[0].user_thr+loop)*3)/5))	
		{
		multi_on_counter++;
		}
	}
	
	if( multi_on_counter >= 3 )
	{
		count_overflow++;
		for( loop = 0; loop < SELF_KEY_NUM ; loop++ )
		{
		//*(g_key_info[method].ref  + loop) = R_Get_Cap_Touch_Sensor_Data(method, _0_BUTTON, loop);
		*(g_key_info[0].touch_cnt  	+ loop)	= 0;
		*(g_key_info[0].drift_cnt     	+ loop)	= 0;
		*(g_key_info[0].drift_add_ref 	+ loop)	= 0x00000000ul;
		}
		
		for(loop = 0;loop<SELF_MAX_GROUP;loop++)
		{
			*(g_key_info[0].in_touch+loop) = 0;
			*(g_key_info[0].out_touch+loop) = 0; 
			*(g_key_info[0].touch_result+loop) = 0;
		}
		
		if(count_overflow >1000)
		{
			{
				TOUCH_CTSU_Reset();
				count_overflow = 0;
			}
		}
		
		multi_on_counter = 0;
	
	}
	else
	{
			count_overflow = 0;
	}
}


uint16_t Touch_LPF(uint16_t Ncount,uint8_t loop)
{
	uint16_t	newData;
	newData = (uint16_t)(Ncount*TOUCH_LPF_COEFFICIENT) + (uint16_t)((1 - TOUCH_LPF_COEFFICIENT)*Filter_ref[loop]);
	Filter_ref[loop] = newData;
	return newData;
}


/*
	IEC61000-4-3 counter measure
	If Ncount<Ref-Thr/2,forbidden the reference refresh
*/
void Touch_Drift_Permission(uint16_t Ncount,uint8_t loop)
{
	Drift_Permission[0] = 1;				//If specific key need to disable this function.set to 1 in any case
	if(loop>0&&loop<SELF_KEY_NUM)
	{
		if(Ncount > (*(g_key_info[0].ref  + loop) - (*(g_key_info[0].user_thr  + loop))/2))
		{
			Drift_Permission[loop] = 1;
		}
		else
		{
			Drift_Permission[loop] = 0;
		}
	}
}

void TOUCH_CTSU_Reset(void)
{
	uint8_t ret_val;
	uint8_t loop;
	
	for( loop = 0; loop < SELF_KEY_NUM ; loop++ )
	{
		//*(g_key_info[method].ref  + loop) = R_Get_Cap_Touch_Sensor_Data(method, _0_BUTTON, loop);
		*(g_key_info[0].touch_cnt  	+ loop)	= 0;
		*(g_key_info[0].drift_cnt     	+ loop)	= 0;
		*(g_key_info[0].drift_add_ref 	+ loop)	= 0x00000000ul;
	}
	
	ret_val = R_Set_Cap_Touch_Create( 0 );                    /* Capacitive touch create API call                */
	if (_0_SUCCESS == ret_val)                                     /* Create result check                             */
	{
		g_ctsu_soft_mode = CTSU_READY_MODE;                        /* CTSU measurement ready mode setting             */
	}
	else
	{
		g_ctsu_soft_mode = CTSU_STOP_MODE;                         /* CTSU measurement stop mode setting              */
	}
}


