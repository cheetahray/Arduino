
/******************************************************************************

  Filename:		udpapp.h
  Description:	UDP app for the WiShield 1.0

 ******************************************************************************

  TCP/IP stack and driver for the WiShield 1.0 wireless devices

  Copyright(c) 2009 Async Labs Inc. All rights reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  Contact Information:
  <asynclabs@asynclabs.com>

   Author               Date        Comment
  ---------------------------------------------------------------
   AsyncLabs			07/11/2009	Initial version

 *****************************************************************************/

#include "uip.h"
#include <string.h>
#include "udpapp.h"
#include "config.h"
#define packetlen 30
#define diff 2
#define STATE_INIT				0
#define STATE_LISTENING         1
#define STATE_HELLO_RECEIVED	2
#define STATE_HELLO_ORDER		3
//#define STATE_NAME_RECEIVED		4
static struct udpapp_state s;
extern char message[packetlen+diff];
void dummy_app_appcall(void)
{
}

void udpapp_init(void)
{
	uip_ipaddr_t addr;
        struct uip_udp_conn *c;

        //uip_ipaddr(&addr, 192,168,1,100);
        uip_ipaddr(&addr, 255,255,255,255);
        c = uip_udp_new(&addr, HTONS(12345));
        if(c != NULL) 
        {
           uip_udp_bind(c, HTONS(12344));
        }

	s.state = STATE_INIT;

	PT_INIT(&s.pt);
}

static unsigned char parse_msg(void)
{
	if (memcmp(uip_appdata, "Hello", 5) == 0) {
		return 1;
	}

	return 0;
}

static void send_request(void)
{
	char str[] = "Hello. What is your name?";
        memset(message, 0x00, packetlen+diff);
        memcpy(message, str, strlen(str));
	uip_send(message, strlen(str));
}

static void send_response(void)
{
	/*
	char i = 0;
	char str[] = "Hello ";

	while ( ( ((char*)uip_appdata)[i] != '\0') && i < packetlen) {
		s.inputbuf[i] = ((char*)uip_appdata)[i];
		i++;
	}
	s.inputbuf[i] = '\0';
        
        memcpy(uip_appdata, str, 6);
	memcpy(uip_appdata+6, s.inputbuf, i+1);
	uip_send(uip_appdata, i+7);
        */
        memset(message, 0x00, packetlen+diff);
        memcpy(message, uip_appdata, packetlen);
        message[packetlen] = 0;
}

static PT_THREAD(handle_connection(void))
{
	PT_BEGIN(&s.pt);

	s.state = STATE_LISTENING;
        
        do {
		PT_WAIT_UNTIL(&s.pt, uip_newdata());

		if(uip_newdata()) {
                    if(parse_msg())
                    {
                        s.state = STATE_HELLO_ORDER;
                        send_request();
			uip_flags &= (~UIP_NEWDATA);
			break;
                    }
                    else
                    {
			s.state = STATE_HELLO_RECEIVED;
                        send_response();
        		uip_flags &= (~UIP_NEWDATA);
			break;
                    }
		}
	} while(s.state < STATE_HELLO_RECEIVED);
        
        s.state = STATE_INIT;

	PT_END(&s.pt);
}

void udpapp_appcall(void)
{
	handle_connection();
}
