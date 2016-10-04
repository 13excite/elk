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

	
# #####################BACKEND############### INFO LOGLEVEL ##########################################################
# BACKEND AND MIDDLEEND PATTERN #################
REQUEST_PRZ (POST)
IPPORT %{IP}:%{POSINT:port}
STYLE_TYPE (baw)|(blueice)|(bluewave)|(cartoon1)|(chuk)|(farm)|(fire)|(hsn)|(ink)|(mononoke_cleaned)|(mosaic_512)|(mosaic_fast)|(mosaic_violet)|(neonpencil)|(picasso)|(spiral)|(zen)
STYLE_TYPE_VIDEO (\w+_video)
STYLE_TYPE_IMG (\w+ _image)
QID_PR (([\da-z]{16}))
WORK_ID_PRIZM (([a-z0-9]*)-([a-z0-9]*)-([a-z0-9]*)-([a-z0-9]*)-([a-z0-9]*))
SQUARE (true)|(false)

# REQUEST VIDEO 
# RETURN VIDEO # FINALLY# stage 1-4
QUERY_VIDEO_BCKND %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: Query \[&_qid=%{QID_PR:prizm_qid}.+ is being sent to worker #\d
REQUEST_BCKND %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} %{WORD}, STYLE type: %{WORD:style_type}, %{REQUEST_PRZ:prizm_request} data len: %{NUMBER:data_len}?%{GREEDYDATA}
RETURN_VIDEO_BCKND_DATA %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} %{DATA} %{NUMBER:data_size}, elapsed: %{NUMBER:elapsed}ms
RETURN_VIDEO_BCKND_PUT_RESULT %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} %{DATA}: %{NUMBER} \(work_id: %{WORK_ID_PRIZM:prizm_work_id}\)
RETURN_VIDEO_BCKND_LAST %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: Query \[qid="%{QID_PR:prizm_qid}"\] %{SYSLOG5424SD} %{DATA}; frontend: %{IP:frontend_ip} times: total\(%{NUMBER:times_total} ms\): queue\(%{NUMBER:times_queue} ms\) \+ worker\(%{NUMBER:times_worker} ms\) answer length: %{NUMBER:answer_lenght}
# #########  NO VIDEO  ###### 
# FIRST Query equally request VIDEO
# STEP 2 NO VIDEo #######style-type need used pettern WORD#######
REQUEST_NO_VIDEO_BCKND %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} STYLE type: %{WORD:style_type}, %{REQUEST_PRZ:prizm_request} data len: %{NUMBER:data_len}, LUA_MEM: %{NUMBER:lua_mem} Kb
# STEP 3 return data NO VIDEO
RETURN_NO_VIDEO_BCKND %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} return data size: %{NUMBER:data_size}, LUA_MEM\(after GC\): %{NUMBER:lua_mem} Kb
# STEP 4 equally RETURN-VIDEO-BCKND-LAST

# ERROR REQUEST BACKEND ##########
ERROR_BCKND_REQUEST %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{GREEDYDATA}

# incoming connection BACKEND
INCOM_CONNECT_BCKND %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: incoming connection: %{IPPORT:incoming_connect}; %{SYSLOG5424SD:hz_che}

# process video & image
PROC_VIDEO_GPU_TIME %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: %{WORD:type_process}: GPUTime: %{NUMBER:gpu_time}
#  ProcessVideo and image: required width:high will be made later 

# ####### IMAGE ##########
# FIRST Query equally request VIDEO
# STEP 2 equally for image and video
# STEP 3 equally for iamge and video
# STEP 4 too
# and step 5

# ################!!!!!!!!!!!!!!MIDDLEND!!!!!!!!!!!#######################
QUERY_MIDDL %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: Query \[&_qid=%{QID_PR:prizm_qid}.+ is being sent to worker #\d
DO_PROCESS_MIDDL %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} Start process \(work_id: %{WORK_ID_PRIZM:prizm_work_id}; boomerang: %{NUMBER:boomerang}\)
MERGE_MIDDL %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} Successfully merged \(chunk_num: %{NUMBER:chunk_num}; elapsed: %{NUMBER:elapsed}ms\)
ANSWER_MIDDL %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: Query \[qid="%{QID_PR:prizm_qid}"\] %{SYSLOG5424SD} %{DATA}; frontend: %{IP:frontend_ip} times: total\(%{NUMBER:times_total} ms\): queue\(%{NUMBER:times_queue} ms\) \+ worker\(%{NUMBER:times_worker} ms\) answer length: %{NUMBER:answer_lenght}

# LOG TYPE 2
PROC_DO_MIDDLE %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} Start process \(work_id: %{WORK_ID_PRIZM:prizm_work_id}; boomerang: %{NUMBER:boomerang}; media_type: %{WORD:media_type}; style: %{WORD:style_type}\)
AVSTREAM_MIDDLE %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[mp4 @ %{BASE16FLOAT:mp4}\] %{GREEDYDATA:message_avstream}

# WARNING level 
WARN_MIDDL %{WORKER:worker} #\d+	\[%{DATETIME_PR:prizm_timestamp}\] %{PRIZMLOGLEVEL:loglevel_prizma}: \[QID=%{QID_PR:prizm_qid}\] %{SYSLOG5424SD} Bad chunk \(work_id: %{WORK_ID_PRIZM:prizm_work_id}; %{GREEDYDATA}
