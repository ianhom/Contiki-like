#define ORIGINAL_CODE 1

#define PROCESS(name, strname)				\
  PROCESS_THREAD(name, ev, data);			\
  struct process name = { NULL, strname,		\
                          process_thread_##name }
                          
#define PROCESS_THREAD(name, ev, data) 				\
static PT_THREAD(process_thread_##name(struct pt *process_pt,	\
				       process_event_t ev,	\
				       process_data_t data))
				      
#define PT_THREAD(name_args) char name_args

#define AUTOSTART_PROCESSES(...)					\
struct process * const autostart_processes[] = {__VA_ARGS__, NULL}

#define PROCESS_BEGIN()             PT_BEGIN(process_pt)

#define PT_BEGIN(pt) { char PT_YIELD_FLAG = 1; if (PT_YIELD_FLAG) {;} LC_RESUME((pt)->lc)

#define LC_RESUME(s) switch(s) { case 0:

#define PROCESS_END()               PT_END(process_pt)

#define PT_END(pt) LC_END((pt)->lc); PT_YIELD_FLAG = 0; \
                   PT_INIT(pt); return PT_ENDED; }
                   
#define LC_END(s) }

#define PT_INIT(pt)   LC_INIT((pt)->lc)

#define LC_INIT(s) s = 0;
