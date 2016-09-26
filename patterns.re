MODULS (\[M\]|\[\d\])
LOGLEVEL (TRACE|DEBUG|NOTICE|INFO|WARN?(?:ING)?|ERR?(?:OR)?|CRIT?(?:ICAL)?|FATAL|SEVERE|EMERG)
DATE (\d{2}\.\d{2}\.\d{2})
TIME (\d{2}:\d{2}:\d{2})
DATETIME %{DATE} %{TIME}
# PID #222222
PID (\#[1-9]+[\d]{1,})

WORKER (worker \#\d{1})
LOGMESSAGE ((TRACE|DEBUG|NOTICE|INFO|WARN?(?:ING)?|ERR?(?:OR)?|CRIT?(?:ICAL)?|FATAL|SEVERE|EMERG))(.*?)(\n|$)

PRIZMALOG %{DATETIME:timestamp_prizma} %{LOGLEVEL:loglevel_prizma} %{LOGMESSAGE:message_prizma}