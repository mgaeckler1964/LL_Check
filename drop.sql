set arraysize 5000
set heading OFF

spool _drop.sql
select 'drop procedure ' || OBJECT_NAME || ';' from user_procedures;
select 'drop view ' || VIEW_NAME || ';' from user_views;
select 'drop sequence ' || SEQUENCE_NAME || ';' from user_sequences;
spool off
@_drop.sql


/*
select 'drop table ' || TABLE_NAME || ';' from user_tables;
*/

drop table HTTP_THREAD;
drop table HTTP_RECURRING;

drop table LLTHREAD_FUNCTIONS;

drop table chart_requests_per_hour;
drop table chart_requests_per_day;

drop table LLTHREAD_SUMMARY_TABLE;
drop table LLTHREAD;
drop table SERVER;

drop table WEB_FUNCTIONS;

drop table chart_web_requests_per_hour;
drop table chart_web_requests_per_day;

drop table WEB_SUMMARY_TABLE;
drop table WEB_LOGS;
drop table WEB_SERVER;

exit;

