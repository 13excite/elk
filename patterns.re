MDATE_PR (\d{2}\.\d{2}\.\d{2})
TIME_PR (\d{2}:\d{2}:\d{2})
DATETIME_PR %{DATE} %{TIME}


QUID_PRIZMA ((\[QI(.*?)(\n|$))|(Quer(.*?)(\n|$)))

PRIZMLOGLEVEL (TRACE|DEBUG|NOTICE|INFO|WARN?(?:ING)?|ERR?(?:OR)?|CRIT?(?:ICAL)?|FATAL|SEVERE|EMERG)FULL_PRIZMA_LOG (%{DATETIME_PR:timestamp_prizma}).*(%{LOGLEVEL:loglevel_prizma})DATE_PR (\d{2}\.\d{2}\.\d{2})


LOGMESSAGE ((TRACE|DEBUG|NOTICE|INFO|WARN?(?:ING)?|ERR?(?:OR)?|CRIT?(?:ICAL)?|FATAL|SEVERE|EMERG))(.*?)(\n|$)
PRIZM_LOGMSG %{LOGMESSAGE}

QUID_PRIZMA ((\[QI(.*?)(\n|$))|(Quer(.*?)(\n|$)))

PRIZMLOGLEVEL (TRACE|DEBUG|NOTICE|INFO|WARN?(?:ING)?|ERR?(?:OR)?|CRIT?(?:ICAL)?|FATAL|SEVERE|EMERG)

FULL_PRIZMA_LOG (%{DATETIME_PR:timestamp_prizma}).*(%{LOGLEVEL:loglevel_prizma})