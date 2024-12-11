<?xml version="1.0" encoding="iso-8859-1" ?>
<setup>
<application title="LL Check" version="3.0.0.82" path="CRESD\LL Check" registry="CRESD\LL Check" />
<bde AliasName="LL_CHECK" RESOURCE="0009" DataPath="" dbVersion="-1" />
<icons Group="LL Check">
<icon title="LL Check" target="PROGRAM\ll_check.exe" main="true" dbUpd="" />
<icon title="BDE Administration" target="BDE\bdeadmin.exe" main="" dbUpd="" />
<icon title="HTTP Check" target="PROGRAM\http_check.exe" main="" dbUpd="" />
</icons>
<source>
<file source="..\..\Object\ll_check.exe" />
<file source="..\..\Object\ll_import.exe" />
<file source="..\..\Object\check_http.exe" />
<file source="..\..\Object\checkHttpService.exe" />
<file source="..\..\Object\http_check.exe" />
<file source="..\..\Object\web_import.exe" />
<file source="..\..\Object\libeay32.dll" />
<file source="..\..\Object\ssleay32.dll" />
<file source="..\..\Object\client.pem" />
<file source="..\..\Object\root.pem" />
</source>
</setup>