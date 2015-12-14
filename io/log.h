#ifndef INCLUDE_LOG_H
#define INCLUDE_LOG_H

#define L_ERROR		-1
#define L_DEBUG		-2
#define L_INFO		-3

/** log_msg
 * 		logs message in a specific mode , USES COM2 port
 */
void log_msg(const int mode, char *buf, int len);


#endif /*INCLUDE_LOG_H */
