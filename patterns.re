# PARSE DATE
MDATE_PR (\d{2}\.\d{2}\.\d{2})
TIME_PR (\d{2}:\d{2}:\d{2})
DATETIME_PR %{DATE} %{TIME}

# WORKER
WORKER (\[M\]|\[\d\])

# PARSE TYPE LOGMSG BCKND LOG
STANDART_MSG_BCKND ((\[QI(.*?)(\n|$))|(Quer(.*?)(\n|$))|(Error oc(.*?)(\n|$))|(ProcessVid(.*?)(\n|$))|(Failed to(.*?)(\n|$)))

# PARSE TYPE LOGMSG MIDDLE LOG
STANDART_MSG_MDDL((Zero-length(.*?)(\n|$))|(Error in chan(.*?)(\n|$))|(\[QI(.*?)(\n|$))|(Quer(.*?)(\n|$))|(MakeOne(.*?)(\n|$))|(Event cal(.*?)(\n|$))|(Kill act(.*?)(\n|$)))

# LOGLEVEL PARSE. NOT USED STANDART %{LOGVEVEL}
PRIZMLOGLEVEL (TRACE|DEBUG|NOTICE|INFO|WARN?(?:ING)?|ERR?(?:OR)?|CRIT?(?:ICAL)?|FATAL|SEVERE|EMERG)

# cut LOGMSG from LOGLEVEL and end line. not valid if used conjunction with PRIZMLOGLEVEL

LOGMESSAGE ((TRACE|DEBUG|NOTICE|INFO|WARN?(?:ING)?|ERROR|CRIT?(?:ICAL)?|FATAL|SEVERE|EMERG))(.*?)(\n|$)
PRIZM_LOGMSG %{LOGMESSAGE}

# complete parse for sending to elk date+loglevel+ all message log

FULL_PRIZMA_LOG (%{DATETIME_PR:timestamp_prizma}).*(%{PRIZMLOGLEVEL:loglevel_prizma})%{GREEDYDATA:prizm_message}

	
# BACKEND###############
# REQUEST BACKEND #################
REQUEST_PRZ (POST)
STYLE_TYPE (baw)|(blueice)|(bluewave)|(cartoon1)|(chuk)|(farm)|(fire)|(hsn)|(ink)|(mononoke_cleaned)|(mosaic_512)|(mosaic_fast)|(mosaic_violet)|(neonpencil)|(picasso)|(spiral)|(zen)
STYLE_TYPE_VIDEO (\w+_video)
QID_PRIZM (([\da-z]{16}))
WORK_ID_PRIZM (([a-z0-9]*)-([a-z0-9]*)-([a-z0-9]*)-([a-z0-9]*)-([a-z0-9]*))
SQUARE (true)|(false)

# REQUEST VIDO 
# RETURN VIDEO # FINALLY# stage 1-4
QUERY_VIDEO_BCKND %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:prizm_log_level}: Query \[&_qid=%{QID_PR:prizm_qid}.+ is being sent to worker #\d
REQUEST_VIDEO_BCKND %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:prism_loglevel}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} VIDEO, STYLE type: %{STYLE_TYPE_VIDEO:style_type}, %{REQUEST_PRZ:prizm_request} data len: %{NUMBER:data_len}, SQUARE: %{SQUARE:square}
RETURN_VIDEO_BCKND %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:prizm_log_level}: \[QID=%{QID_PRIZM:prizm_qid}\] %{SYSLOG5424SD} VIDEO return data size: %{NUMBER:data_size}, elapsed: %{NUMBER:elapsed}ms
RETURN_VIDEO_BCKND_PUT_RESULT %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:prism_loglevel}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} Counter value after decrement: 3 \(work_id: %{WORK_ID_PRIZM:prizm_work_id}\)
RETURN_VIDEO_BCKND_LAST %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:prizm_log_level}: Query \[qid="%{QID_PR:prizm_qid}"\] %{SYSLOG5424SD} answer has been received from worker #1; frontend: %{IP:frontend_ip} times: total\(%{NUMBER:times_total} ms\): queue\(%{NUMBER:times_queue} ms\) \+ worker\(%{NUMBER:times_worker} ms\) answer length: %{NUMBER:answer_lenght}

# NOT VIDEO 
# FIRST Query equally request VIDEO
# STEP 2 non VIDEO
%{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:prism_loglevel}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} STYLE type: %{WORD:style_type}, %{REQUEST_PRZ:prizm_request} data len: %{NUMBER:data_len}, LUA_MEM: %{NUMBER:lua_mem} Kb
# STEP 3 return data non video
 



