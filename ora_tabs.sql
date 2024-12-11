/*
========================================================================================================
	Livelink Logs
========================================================================================================
*/

/*
	server
*/
create table SERVER
(
	ID					INTEGER			NOT NULL	PRIMARY KEY,
	SERVER_NAME			VARCHAR(255),
	PATH				VARCHAR(1955)
);

create unique index SERVER_NAME_IDX on SERVER ( SERVER_NAME );

/*
	llthread
*/
create table LLTHREAD
(
	ID					INTEGER			NOT NULL	PRIMARY KEY,
	SERVER              INTEGER			NOT NULL	REFERENCES	SERVER,
	REQUEST_DATE_TIME	DATE,
	START_TICK			INTEGER,
	THREAD				NUMBER,
	FUNC				VARCHAR2(255)	NOT NULL,
	EXEC_TIME			NUMBER,
	SQL_TIME			NUMBER,
	SQL_COUNT			INTEGER,
	GENERATE_TIME		NUMBER,
	OBJECT_ID			INTEGER,
	PARENT_ID			INTEGER,
	MISRC_ARGS			VARCHAR2(255),
	ERROR				VARCHAR2(255),
	REQ_SQL_TIME		NUMBER,
	REQ_SQL_TIME_LOGED	NUMBER,
	REQ_SQL_COUNT		INTEGER,
	REC_FETCHED			INTEGER,
	REC_CHANGED			INTEGER
);

create sequence ID_SEQ;

create or replace trigger LLTHREAD_INSERT
before insert on LLTHREAD for each row
declare
	newId	Integer;
begin
	select ID_SEQ.NEXTVAL into newId from DUAL;

	:NEW.ID := newId;
end;
/

create index FUNC_IDX on LLTHREAD ( FUNC, EXEC_TIME );
create unique index REQUEST_DATE_IDX on LLTHREAD
( 
	REQUEST_DATE_TIME, SERVER, THREAD, START_TICK 
);
create index SERVER_IDX on LLTHREAD ( SERVER );
create index TIME_IDX on LLTHREAD ( EXEC_TIME );

create view LLTHREAD_SUMMARY_VIEW as
	select	SERVER, 
			trunc( REQUEST_DATE_TIME ) as REQUEST_DATE_TIME,
			to_number( to_char( REQUEST_DATE_TIME, 'HH24' ) ) as HOUR,
			FUNC,
			OBJECT_ID,
			sum( exec_time ) as exec_time,
			sum( sql_time ) as sql_time,
			sum( generate_time ) as generate_time,
			count(*) as num_requests,
			sum( REQ_SQL_TIME ) as REQ_SQL_TIME,
			sum( REQ_SQL_TIME_LOGED ) as REQ_SQL_TIME_LOGED,
			sum( REQ_SQL_COUNT ) as REQ_SQL_COUNT,
			sum( REC_FETCHED ) as REC_FETCHED,
			sum( REC_CHANGED ) as REC_CHANGED
	from llthread
	group by SERVER, 
			trunc( REQUEST_DATE_TIME ),
			to_number( to_char( REQUEST_DATE_TIME, 'HH24' ) ),
			FUNC,
			OBJECT_ID
;

/*
	summary table
*/
create table LLTHREAD_SUMMARY_TABLE
(
	SERVER              INTEGER			NOT NULL	REFERENCES	SERVER,
	REQUEST_DATE_TIME	DATE,
	HOUR				INTEGER,
	FUNC				VARCHAR2(255)	NOT NULL,
	OBJECT_ID			INTEGER,
	EXEC_TIME			NUMBER,
	SQL_TIME			NUMBER,
	GENERATE_TIME		NUMBER,
	NUM_REQUESTS		INTEGER,
	REQ_SQL_TIME		NUMBER,
	REQ_SQL_TIME_LOGED	NUMBER,
	REQ_SQL_COUNT		INTEGER,
	REC_FETCHED			INTEGER,
	REC_CHANGED			INTEGER
);
create index LLTHREAD_SUMMARY_IDX on LLTHREAD_SUMMARY_TABLE (REQUEST_DATE_TIME, HOUR);
create unique index SUMMARY_REQUEST_DATE_IDX on LLTHREAD_SUMMARY_TABLE
( 
	SERVER, REQUEST_DATE_TIME, HOUR, FUNC, OBJECT_ID
);

create view LLTHREAD_SUMMARY as
	select * from LLTHREAD_SUMMARY_TABLE
	union all
	select * from LLTHREAD_SUMMARY_VIEW
;

/*
	some chart data
*/

create table chart_requests_per_day
(
	day					date			not null,
	server				integer			not null references server,
	num_requests		integer			not null,
	exec_time			number			not null,
	sql_time			number			not null,
	generate_time		number			not null,
	REQ_SQL_TIME		NUMBER,
	REQ_SQL_TIME_LOGED	NUMBER,
	REQ_SQL_COUNT		INTEGER,
	REC_FETCHED			INTEGER,
	REC_CHANGED			INTEGER
);

create unique index chart_requests_per_day_idx on chart_requests_per_day( day, server );

create table chart_requests_per_hour
(
	day					date			not null,
	hour				integer			not null,
	server				integer			not null references server,
	num_requests		integer			not null,
	exec_time			number			not null,
	sql_time			number			not null,
	generate_time		number			not null,
	REQ_SQL_TIME		NUMBER,
	REQ_SQL_TIME_LOGED	NUMBER,
	REQ_SQL_COUNT		INTEGER,
	REC_FETCHED			INTEGER,
	REC_CHANGED			INTEGER
);
create unique index chart_requests_per_hour_idx on chart_requests_per_hour( day, hour, server );


/*
	functions table
*/
create table LLTHREAD_FUNCTIONS
(
	FUNC				VARCHAR2(255)	NOT NULL,
	OBJECT_ID			INTEGER
);

create unique index LLTHREAD_FUNCTIONS_IDX on LLTHREAD_FUNCTIONS ( FUNC, OBJECT_ID );


/*
	stored procedures
*/

/*
	clearChart
	==========

	delete all pre calculated chart data
*/
create or replace procedure clearChart is
begin
	delete from chart_requests_per_hour;
	commit;
	delete from chart_requests_per_day;
	commit;
end;
/
show errors;


/*
	calcChart
	=========

	pre calculate some charts
*/
create or replace procedure calcChart is
begin
	clearChart;
	insert into chart_requests_per_day
	(
		day,
		server,
		exec_time,
		sql_time,
		generate_time,
		num_requests,
		REQ_SQL_TIME,
		REQ_SQL_TIME_LOGED,
		REQ_SQL_COUNT,
		REC_FETCHED,
		REC_CHANGED
	)
	select	trunc(request_date_time), 
			server,
			sum(exec_time) as exec_time,
			sum(sql_time) as sql_time,
			sum(generate_time) as generate_time,
			sum(num_requests) as num_requests,
			sum( REQ_SQL_TIME ) as REQ_SQL_TIME,
			sum( REQ_SQL_TIME_LOGED ) as REQ_SQL_TIME_LOGED,
			sum( REQ_SQL_COUNT ) as REQ_SQL_COUNT,
			sum( REC_FETCHED ) as REC_FETCHED,
			sum( REC_CHANGED ) as REC_CHANGED
	from	LLTHREAD_SUMMARY
	group by trunc( request_date_time), server;
	commit;

	insert into chart_requests_per_hour
	(
		day,
		hour,
		server,
		exec_time,
		sql_time,
		generate_time,
		num_requests,
		REQ_SQL_TIME,
		REQ_SQL_TIME_LOGED,
		REQ_SQL_COUNT,
		REC_FETCHED,
		REC_CHANGED
	)
	select	trunc(request_date_time),
			hour,
			server,
			sum(exec_time) as exec_time,
			sum(sql_time) as sql_time,
			sum(generate_time) as generate_time,
			sum(num_requests) as num_requests,
			sum( REQ_SQL_TIME ) as REQ_SQL_TIME,
			sum( REQ_SQL_TIME_LOGED ) as REQ_SQL_TIME_LOGED,
			sum( REQ_SQL_COUNT ) as REQ_SQL_COUNT,
			sum( REC_FETCHED ) as REC_FETCHED,
			sum( REC_CHANGED ) as REC_CHANGED
	from	LLTHREAD_SUMMARY
	group by trunc(request_date_time), hour, server;
	commit;
end;
/
show errors;

/*
	deleteFastServer
	================
	delete all entries in llthread for one server
	keep n days in table
*/
drop procedure deleteFastServer;
create procedure deleteFastServer( daysToKeep in integer, theServer in integer ) is
	maxDate		Integer;
	theDate		Integer;
begin
	select to_number( to_char( SYSDATE, 'J' ) ) - daysToKeep into maxDate from dual;

	select min(to_number( to_char( REQUEST_DATE_TIME, 'J' ) )) into theDate from llthread where server = theServer;
	if theDate is not null then
		while theDate < maxDate loop
			delete from llthread
			where	server=theServer and
					to_number( to_char( REQUEST_DATE_TIME, 'J' ) ) = theDate;
			commit;
			theDate := theDate +1;
		end loop;
	end if;
end;
/
show errors;

/*
	deleteFast
	==========
	delete all entries in llthread for all servers
	keep n days in table
*/

drop procedure deleteFast;
create procedure deleteFast( daysToKeep in integer ) is
	Cursor serverTC is
		select id from server;

	theServer	Integer;
begin
	for serverRec in serverTC loop
		theServer := serverRec.id;
		deleteFastServer( daysToKeep, theServer );
	end loop;
end;
/ 
show errors;

/*
	deleteOld
	=========
	delete all entries in llthread that have been summarized
*/
drop procedure deleteOld;
create procedure deleteOld is
	minDate	Date;
	Cursor	summaryTC(startDate in Date) is
		select * from llthread_summary_table where request_date_time >= startDate;
begin
	select min(REQUEST_DATE_TIME) into minDate from llthread;

	for summaryRec in summaryTC(minDate) loop
		delete from llthread 
		where	
			SERVER												= summaryRec.SERVER and 
			trunc( REQUEST_DATE_TIME )							= summaryRec.REQUEST_DATE_TIME and
			to_number( to_char( REQUEST_DATE_TIME, 'HH24' ) )	= summaryRec.HOUR and
			FUNC												= summaryRec.FUNC and
			OBJECT_ID											= summaryRec.OBJECT_ID;
		--- to avoid problems with rollback segments
		commit;
	end loop;
end;
/
show errors;

/*
	summarizeServer
	===============
	summarize all entries for one server
	keep n days
*/
create or replace procedure summarizeServer( daysToKeep in integer, theServer in Integer ) is
	Cursor	summaryTC is
		select	* 
		from	llthread_summary_view
		where	server = theServer and 
				to_number( to_char( REQUEST_DATE_TIME, 'J' ) ) < to_number( to_char( SYSDATE, 'J' ) ) - daysToKeep;
begin
	for summaryRec in summaryTC loop
		begin
			insert into llthread_summary_table
			(
				SERVER,
				REQUEST_DATE_TIME,
				HOUR,
				FUNC,
				OBJECT_ID,
				EXEC_TIME,
				SQL_TIME,
				GENERATE_TIME,
				NUM_REQUESTS,
				REQ_SQL_TIME,
				REQ_SQL_TIME_LOGED,
				REQ_SQL_COUNT,
				REC_FETCHED,
				REC_CHANGED
			)
			values
			(
				summaryRec.SERVER,
				summaryRec.REQUEST_DATE_TIME,
				summaryRec.HOUR,
				summaryRec.FUNC,
				summaryRec.OBJECT_ID,
				summaryRec.EXEC_TIME,
				summaryRec.SQL_TIME,
				summaryRec.GENERATE_TIME,
				summaryRec.NUM_REQUESTS,
				summaryRec.REQ_SQL_TIME,
				summaryRec.REQ_SQL_TIME_LOGED,
				summaryRec.REQ_SQL_COUNT,
				summaryRec.REC_FETCHED,
				summaryRec.REC_CHANGED
			);
			--- to avoid problems with rollback segments
			commit;
		exception
			when DUP_VAL_ON_INDEX then
				rollback;
		end;
	end loop;

	deleteFastServer( daysToKeep, theServer );
end;
/
show errors;

/*
	summarizeServer
	===============
	summarize all entries for all servers
	keep n days
*/
drop procedure summarize;
create procedure summarize( daysToKeep in integer ) is
	Cursor serverTC is
		select id from server;

	theServer	Integer;
begin
	for serverRec in serverTC loop
		theServer := serverRec.id;
		summarizeServer( daysToKeep, theServer );
	end loop;
end;
/
show errors;

/*
========================================================================================================
	HTTP Client Logs
========================================================================================================
*/

/*
	HTTP_THREAD
*/
create table HTTP_THREAD
(
	ID					INTEGER			NOT NULL	PRIMARY KEY,
	HTTP_URL			VARCHAR(1995)	NOT NULL,
	HTTP_COOKIES		VARCHAR(1995),
	REQUEST_DATE_TIME	DATE			DEFAULT SYSDATE	NOT NULL,
	LOOP_COUNT			INTEGER			NOT NULL,
	USER_COUNT			INTEGER			NOT NULL,
	AVG_TIME			NUMBER
);

create or replace trigger HTTP_THREAD_INSERT
before insert on HTTP_THREAD for each row
declare
	newId	Integer;
begin
	select ID_SEQ.NEXTVAL into newId from DUAL;

	:NEW.ID := newId;
end;
/

alter table HTTP_THREAD add
(
	PROXY_SERVER	VARCHAR2(255),
	PROXY_PORT		INTEGER,
	COMPLETE_FLAG	VARCHAR2(1),
	LINK_CHECK		VARCHAR2(1),
	TOTAL_SIZE		INTEGER,
	NUM_FILES		INTEGER,
	MAX_FILES		INTEGER
);	

create table HTTP_RECURRING
(
	ID					INTEGER			NOT NULL	PRIMARY KEY,
	HTTP_URL			VARCHAR(1995)	NOT NULL,
	HTTP_COOKIES		VARCHAR(1995),
	PROXY_SERVER		VARCHAR2(255),
	PROXY_PORT			INTEGER,
	INTERVAL			INTEGER			NOT NULL,
	NEXT_START			DATE			DEFAULT SYSDATE,
	MAX_TIME			NUMBER			NOT NULL,
	LAST_TIME			NUMBER,
	LAST_STATUS			INTEGER,
	E_MAIL_ALERT		VARCHAR(255),
	SMTP_SERVER			VARCHAR(255),
	SMTP_USER			VARCHAR(255),
	SMTP_PORT			INTEGER
);


create index HTTP_RECURRING_IDX on HTTP_RECURRING ( NEXT_START );

create or replace trigger HTTP_RECURRING_INSERT
before insert on HTTP_RECURRING for each row
declare
	newId	Integer;
begin
	select ID_SEQ.NEXTVAL into newId from DUAL;

	:NEW.ID := newId;
end;
/



/*
========================================================================================================
	HTTP Server Logs
========================================================================================================
*/
/*
	web server
*/
create table WEB_SERVER
(
	ID					INTEGER			NOT NULL	PRIMARY KEY,
	SERVER_NAME			VARCHAR(255),
	PATH				VARCHAR(1955)
);

create unique index WEB_SERVER_NAME_IDX on WEB_SERVER ( SERVER_NAME );

create table WEB_LOGS
(
	ID					INTEGER			NOT NULL	PRIMARY KEY,
	SERVER              INTEGER			NOT NULL	REFERENCES	WEB_SERVER,
	REQUEST_DATE_TIME	DATE			NOT NULL,
	HTTP_METHOD			VARCHAR(32),
	HTTP_URL			VARCHAR(255)	NOT NULL,	
	HTTP_QUERY			VARCHAR(255),
	HTTP_COOKIES		VARCHAR(255),
	HTTP_AGENT			VARCHAR(255),
	HTTP_STATUS			INTEGER			NOT NULL,
	HTTP_SUB_STATUS		INTEGER,
	HTTP_WIN_STATUS		INTEGER,
	BYTES_RECEIVED		INTEGER,
	BYTES_SENT			INTEGER,
	EXEC_TIME			INTEGER
);

create index WEB_DATE_IDX on WEB_LOGS ( REQUEST_DATE_TIME, HTTP_URL, HTTP_QUERY, EXEC_TIME );
create index WEB_URL_IDX on WEB_LOGS ( HTTP_URL, HTTP_QUERY, EXEC_TIME );
create index WEB_TIME_IDX on WEB_LOGS ( EXEC_TIME );

create or replace trigger WEB_LOGS_INSERT
before insert on WEB_LOGS for each row
declare
	newId	Integer;
begin
	select ID_SEQ.NEXTVAL into newId from DUAL;

	:NEW.ID := newId;
end;
/

/*
	summary table
*/
create table WEB_SUMMARY_TABLE
(
	SERVER              INTEGER			NOT NULL	REFERENCES	WEB_SERVER,
	REQUEST_DATE_TIME	DATE,
	HOUR				INTEGER,
	HTTP_URL			VARCHAR2(255)	NOT NULL,
	HTTP_QUERY			VARCHAR2(255),
	EXEC_TIME			INTEGER,
	NUM_REQUESTS		INTEGER
);

create index WEB_SUMMARY_IDX on WEB_SUMMARY_TABLE (REQUEST_DATE_TIME, HOUR);
create unique index WEB_REQUEST_DATE_IDX on WEB_SUMMARY_TABLE
( 
	SERVER, REQUEST_DATE_TIME, HOUR, HTTP_URL, HTTP_QUERY
);

create view WEB_SUMMARY_VIEW as
	select	SERVER, 
			trunc( REQUEST_DATE_TIME ) as REQUEST_DATE_TIME,
			to_number( to_char( REQUEST_DATE_TIME, 'HH24' ) ) as HOUR,
			HTTP_URL,
			HTTP_QUERY,
			sum( exec_time ) as exec_time,
			count(*) as num_requests
	from WEB_LOGS
	group by SERVER, 
			trunc( REQUEST_DATE_TIME ),
			to_number( to_char( REQUEST_DATE_TIME, 'HH24' ) ),
			HTTP_URL,
			HTTP_QUERY
;

create view WEB_SUMMARY as
	select * from WEB_SUMMARY_TABLE
	union all
	select * from WEB_SUMMARY_VIEW
;



/*
	functions table
*/
create table WEB_FUNCTIONS
(
	HTTP_URL			VARCHAR2(255)	NOT NULL,
	HTTP_QUERY			VARCHAR2(255)
);

create unique index WEB_FUNCTIONS_IDX on WEB_FUNCTIONS ( HTTP_URL, HTTP_QUERY );


/*
	some chart data
*/

drop table chart_web_requests_per_day;
create table chart_web_requests_per_day
(
	day				date			not null,
	server			integer			not null references web_server,
	num_requests	integer			not null,
	exec_time		integer			not null
);
create unique index chart_web_requests_per_day_idx on chart_web_requests_per_day( day, server );

drop table chart_web_requests_per_hour;
create table chart_web_requests_per_hour
(
	day				date			not null,
	hour			integer			not null,
	server			integer			not null references web_server,
	num_requests	integer			not null,
	exec_time		number			not null
);
create unique index chart_webRequestsPerHourIdx on chart_web_requests_per_hour( day, hour, server );

/*
	deleteFastServer
	================
	delete all entries in llthread for one server
	keep n days in table
*/
create or replace procedure webDeleteFastServer( daysToKeep in integer, theServer in integer ) is
	maxDate		Integer;
	theDate		Integer;
begin
	select to_number( to_char( SYSDATE, 'J' ) ) - daysToKeep into maxDate from dual;

	select min(to_number( to_char( REQUEST_DATE_TIME, 'J' ) )) into theDate from web_logs where server = theServer;
	if theDate is not null then
		while theDate < maxDate loop
			delete from web_logs
			where	server=theServer and
					to_number( to_char( REQUEST_DATE_TIME, 'J' ) ) = theDate;
			commit;
			theDate := theDate +1;
		end loop;
	end if;
end;
/
show errors;

/*
	deleteFast
	==========
	delete all entries in llthread for all servers
	keep n days in table
*/

create or replace procedure webDeleteFast( daysToKeep in integer ) is
	Cursor serverTC is
		select id from web_server;

	theServer	Integer;
begin
	for serverRec in serverTC loop
		theServer := serverRec.id;
		webDeleteFastServer( daysToKeep, theServer );
	end loop;
end;
/ 
show errors;

/*
	summarizeServer
	===============
	summarize all entries for one server
	keep n days
*/
create or replace procedure webSummarizeServer( daysToKeep in integer, theServer in Integer ) is
	Cursor	summaryTC is
		select	* 
		from	web_summary_view
		where	server = theServer and 
				to_number( to_char( REQUEST_DATE_TIME, 'J' ) ) < to_number( to_char( SYSDATE, 'J' ) ) - daysToKeep;
begin
	for summaryRec in summaryTC loop
		begin
			insert into web_summary_table
			(
				SERVER,
				REQUEST_DATE_TIME,
				HOUR,
				HTTP_URL,
				HTTP_QUERY,
				EXEC_TIME,
				NUM_REQUESTS
			)
			values
			(
				summaryRec.SERVER,
				summaryRec.REQUEST_DATE_TIME,
				summaryRec.HOUR,
				summaryRec.HTTP_URL,
				summaryRec.HTTP_QUERY,
				summaryRec.EXEC_TIME,
				summaryRec.NUM_REQUESTS
			);
			--- to avoid problems with rollback segments
			commit;
		exception
			when DUP_VAL_ON_INDEX then
				rollback;
		end;
	end loop;

	webDeleteFastServer( daysToKeep, theServer );
end;
/
show errors;

/*
	summarizeServer
	===============
	summarize all entries for all servers
	keep n days
*/
create or replace procedure webSummarize( daysToKeep in integer ) is
	Cursor serverTC is
		select id from web_server;

	theServer	Integer;
begin
	for serverRec in serverTC loop
		theServer := serverRec.id;
		webSummarizeServer( daysToKeep, theServer );
	end loop;
end;
/
show errors;

/*
	clearChart
	==========

	delete all pre calculated chart data
*/
create or replace procedure clearWebChart is
begin
	delete from chart_web_requests_per_hour;
	commit;
	delete from chart_web_requests_per_day;
	commit;
end;
/
show errors;

/*
	calcChart
	=========

	pre calculate some charts
*/
create or replace procedure calcWebChart is
begin
	clearWebChart;
	insert into chart_web_requests_per_day
	(
		day,
		server,
		exec_time,
		num_requests
	)
	select	trunc(request_date_time), 
			server,
			sum(exec_time) as exec_time,
			sum(num_requests) as num_requests
	from	WEB_SUMMARY
	group by trunc( request_date_time), server;
	commit;

	insert into chart_web_requests_per_hour
	(
		day,
		hour,
		server,
		exec_time,
		num_requests
	)
	select	trunc(request_date_time),
			hour,
			server,
			sum(exec_time) as exec_time,
			sum(num_requests) as num_requests
	from	WEB_SUMMARY
	group by trunc(request_date_time), hour, server;
	commit;
end;
/
show errors;
