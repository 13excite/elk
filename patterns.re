# PARSE DATE
MDATE_PR (\d{2}\.\d{2}\.\d{2})
TIME_PR (\d{2}:\d{2}:\d{2})
DATETIME_PR %{DATE} %{TIME}

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


# BACKEND
# REQUEST BACKEND 
REQUEST_PRZ (POST)
STYLE_TYPE (baw)|(blueice)|(bluewave)|(cartoon1)|(chuk)|(farm)|(fire)|(hsn)|(ink)|(mononoke_cleaned)|(mosaic_512)|(mosaic_fast)|(mosaic_violet)|(neonpencil)|(picasso)|(spiral)|(zen)
