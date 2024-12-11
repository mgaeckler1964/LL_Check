object theDataModule: TtheDataModule
  OldCreateOrder = False
  Left = 603
  Top = 459
  Height = 615
  Width = 951
  object ServerTable: TTable
    BeforeDelete = ServerTableBeforeDelete
    DatabaseName = 'llCheck_DB'
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'SERVER_NAME'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'PATH'
        DataType = ftMemo
        Size = 1955
      end>
    IndexDefs = <
      item
        Name = 'SERVER_NAME_IDX'
        Fields = 'SERVER_NAME'
        Options = [ixUnique]
      end
      item
        Name = 'SYS_C002161'
        Fields = 'ID'
        Options = [ixUnique]
      end>
    StoreDefs = True
    TableName = 'SERVER'
    Left = 24
    Top = 16
    object ServerTableID: TFloatField
      FieldName = 'ID'
      Required = True
    end
    object ServerTableSERVER_NAME: TStringField
      DisplayLabel = 'Server Name'
      DisplayWidth = 32
      FieldName = 'SERVER_NAME'
      Size = 255
    end
    object ServerTablePATH: TMemoField
      FieldName = 'PATH'
      Visible = False
      BlobType = ftMemo
      Size = 1955
    end
  end
  object llThreadTable: TTable
    DatabaseName = 'llCheck_DB'
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'SERVER'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'REQUEST_DATE_TIME'
        DataType = ftDateTime
      end
      item
        Name = 'START_TICK'
        DataType = ftFloat
      end
      item
        Name = 'THREAD'
        DataType = ftFloat
      end
      item
        Name = 'FUNC'
        Attributes = [faRequired]
        DataType = ftString
        Size = 255
      end
      item
        Name = 'EXEC_TIME'
        DataType = ftFloat
      end
      item
        Name = 'SQL_TIME'
        DataType = ftFloat
      end
      item
        Name = 'SQL_COUNT'
        DataType = ftFloat
      end
      item
        Name = 'GENERATE_TIME'
        DataType = ftFloat
      end
      item
        Name = 'OBJECT_ID'
        DataType = ftFloat
      end
      item
        Name = 'PARENT_ID'
        DataType = ftFloat
      end
      item
        Name = 'MISRC_ARGS'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'ERROR'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'REQ_SQL_TIME'
        DataType = ftFloat
      end
      item
        Name = 'REQ_SQL_TIME_LOGED'
        DataType = ftFloat
      end
      item
        Name = 'REQ_SQL_COUNT'
        DataType = ftFloat
      end
      item
        Name = 'REC_FETCHED'
        DataType = ftFloat
      end
      item
        Name = 'REC_CHANGED'
        DataType = ftFloat
      end>
    IndexDefs = <
      item
        Name = 'FUNC_IDX'
        Fields = 'FUNC;EXEC_TIME'
      end
      item
        Name = 'REQUEST_DATE_IDX'
        Fields = 'REQUEST_DATE_TIME;SERVER;THREAD;START_TICK'
        Options = [ixUnique]
      end
      item
        Name = 'SERVER_IDX'
        Fields = 'SERVER'
      end
      item
        Name = 'SYS_C002197'
        Fields = 'ID'
        Options = [ixUnique]
      end
      item
        Name = 'TIME_IDX'
        Fields = 'EXEC_TIME'
      end>
    StoreDefs = True
    TableName = 'LLTHREAD'
    Left = 120
    Top = 16
    object llThreadTableID: TFloatField
      FieldName = 'ID'
      Required = True
      Visible = False
    end
    object llThreadTableSERVER: TFloatField
      FieldName = 'SERVER'
      Required = True
      Visible = False
    end
    object llThreadTableSERVER_NAME: TStringField
      DisplayLabel = 'Server'
      FieldKind = fkLookup
      FieldName = 'SERVER_NAME'
      LookupDataSet = ServerTable
      LookupKeyFields = 'ID'
      LookupResultField = 'SERVER_NAME'
      KeyFields = 'SERVER'
      Lookup = True
    end
    object llThreadTableREQUEST_DATE_TIME: TDateTimeField
      DisplayLabel = 'Date'
      FieldName = 'REQUEST_DATE_TIME'
    end
    object llThreadTableSTART_TICK: TFloatField
      FieldName = 'START_TICK'
      Visible = False
    end
    object llThreadTableTHREAD: TFloatField
      FieldName = 'THREAD'
      Visible = False
    end
    object llThreadTableFUNC: TStringField
      DisplayLabel = 'Function'
      DisplayWidth = 32
      FieldName = 'FUNC'
      Required = True
      Size = 255
    end
    object llThreadTableEXEC_TIME: TFloatField
      DisplayLabel = 'Exec. Time'
      FieldName = 'EXEC_TIME'
    end
    object llThreadTableSQL_TIME: TFloatField
      DisplayLabel = 'SQL Time'
      FieldName = 'SQL_TIME'
    end
    object llThreadTableSQL_COUNT: TFloatField
      DisplayLabel = 'SQL Count'
      FieldName = 'SQL_COUNT'
    end
    object llThreadTableGENERATE_TIME: TFloatField
      DisplayLabel = 'HTML Time'
      FieldName = 'GENERATE_TIME'
    end
    object llThreadTableOBJECT_ID: TFloatField
      DisplayLabel = 'Object ID'
      FieldName = 'OBJECT_ID'
    end
    object llThreadTablePARENT_ID: TFloatField
      FieldName = 'PARENT_ID'
      Visible = False
    end
    object llThreadTableMISRC_ARGS: TStringField
      DisplayLabel = 'Query String'
      DisplayWidth = 46
      FieldName = 'MISRC_ARGS'
      Size = 255
    end
    object llThreadTableERROR: TStringField
      DisplayLabel = 'Error'
      DisplayWidth = 32
      FieldName = 'ERROR'
      Size = 255
    end
    object llThreadTableREQ_SQL_TIME: TFloatField
      DisplayLabel = 'Req. SQL Time'
      FieldName = 'REQ_SQL_TIME'
    end
    object llThreadTableREQ_SQL_TIME_LOGED: TFloatField
      DisplayLabel = 'Req. SQL Time Loged'
      FieldName = 'REQ_SQL_TIME_LOGED'
    end
    object llThreadTableREQ_SQL_COUNT: TFloatField
      DisplayLabel = 'Req. SQL Count'
      FieldName = 'REQ_SQL_COUNT'
    end
    object llThreadTableREC_FETCHED: TFloatField
      DisplayLabel = 'Rec. Fetched'
      FieldName = 'REC_FETCHED'
    end
    object llThreadTableREC_CHANGED: TFloatField
      DisplayLabel = 'Recs Changed'
      FieldName = 'REC_CHANGED'
    end
  end
  object HttpTable: TTable
    DatabaseName = 'llCheck_DB'
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'HTTP_URL'
        Attributes = [faRequired]
        DataType = ftMemo
        Size = 1995
      end
      item
        Name = 'HTTP_COOKIES'
        DataType = ftMemo
        Size = 1995
      end
      item
        Name = 'REQUEST_DATE_TIME'
        Attributes = [faRequired]
        DataType = ftDateTime
      end
      item
        Name = 'LOOP_COUNT'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'USER_COUNT'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'AVG_TIME'
        DataType = ftFloat
      end
      item
        Name = 'PROXY_SERVER'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'PROXY_PORT'
        DataType = ftFloat
      end
      item
        Name = 'COMPLETE_FLAG'
        DataType = ftString
        Size = 1
      end
      item
        Name = 'LINK_CHECK'
        DataType = ftString
        Size = 1
      end
      item
        Name = 'TOTAL_SIZE'
        DataType = ftFloat
      end
      item
        Name = 'NUM_FILES'
        DataType = ftFloat
      end
      item
        Name = 'MAX_FILES'
        DataType = ftFloat
      end>
    IndexDefs = <
      item
        Name = 'SYS_C002171'
        Fields = 'ID'
        Options = [ixUnique]
      end>
    StoreDefs = True
    TableName = 'HTTP_THREAD'
    Left = 24
    Top = 128
    object HttpTableID: TFloatField
      FieldName = 'ID'
      Required = True
    end
    object HttpTableHTTP_URL: TMemoField
      FieldName = 'HTTP_URL'
      Required = True
      BlobType = ftMemo
      Size = 1995
    end
    object HttpTableHTTP_COOKIES: TMemoField
      FieldName = 'HTTP_COOKIES'
      BlobType = ftMemo
      Size = 1995
    end
    object HttpTableREQUEST_DATE_TIME: TDateTimeField
      FieldName = 'REQUEST_DATE_TIME'
      Required = True
    end
    object HttpTableLOOP_COUNT: TFloatField
      FieldName = 'LOOP_COUNT'
      Required = True
    end
    object HttpTableUSER_COUNT: TFloatField
      FieldName = 'USER_COUNT'
      Required = True
    end
    object HttpTableAVG_TIME: TFloatField
      FieldName = 'AVG_TIME'
    end
    object HttpTablePROXY_SERVER: TStringField
      FieldName = 'PROXY_SERVER'
      Size = 255
    end
    object HttpTablePROXY_PORT: TFloatField
      FieldName = 'PROXY_PORT'
    end
    object HttpTableCOMPLETE_FLAG: TStringField
      FieldName = 'COMPLETE_FLAG'
      Size = 1
    end
    object HttpTableLINK_CHECK: TStringField
      FieldName = 'LINK_CHECK'
      Size = 1
    end
    object HttpTableTOTAL_SIZE: TFloatField
      FieldName = 'TOTAL_SIZE'
    end
    object HttpTableNUM_FILES: TFloatField
      FieldName = 'NUM_FILES'
    end
    object HttpTableMAX_FILES: TFloatField
      FieldName = 'MAX_FILES'
    end
  end
  object llCheck_DB: TDatabase
    AliasName = 'LL_CHECK'
    Connected = True
    DatabaseName = 'llCheck_DB'
    LoginPrompt = False
    Params.Strings = (
      'USER NAME=ll_check'
      'PASSWORD=ll_check')
    SessionName = 'Default'
    Left = 24
    Top = 192
  end
  object llFunctionsTable: TTable
    DatabaseName = 'llCheck_DB'
    FieldDefs = <
      item
        Name = 'FUNC'
        Attributes = [faRequired]
        DataType = ftString
        Size = 255
      end
      item
        Name = 'OBJECT_ID'
        DataType = ftFloat
      end>
    IndexName = 'LLTHREAD_FUNCTIONS_IDX'
    StoreDefs = True
    TableName = 'LLTHREAD_FUNCTIONS'
    Left = 120
    Top = 72
    object llFunctionsTableFUNC: TStringField
      FieldName = 'FUNC'
      Required = True
      Size = 255
    end
    object llFunctionsTableOBJECT_ID: TFloatField
      FieldName = 'OBJECT_ID'
    end
  end
  object updateLLFunctionsQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'insert into LLTHREAD_FUNCTIONS'
      '('
      #9'FUNC,'
      #9'OBJECT_ID'
      ')'
      'select distinct lower(FUNC), object_id'
      'from LLTHREAD_SUMMARY'
      '')
    Left = 224
    Top = 80
  end
  object SummarizeServer: TStoredProc
    DatabaseName = 'llCheck_DB'
    StoredProcName = 'SUMMARIZESERVER'
    Left = 32
    Top = 72
    ParamData = <
      item
        DataType = ftFloat
        Name = 'DAYSTOKEEP'
        ParamType = ptInput
        Value = 0
      end
      item
        DataType = ftFloat
        Name = 'THESERVER'
        ParamType = ptInput
        Value = 0
      end>
  end
  object llAnalyzerTables: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select '#39'table'#39' as type, table_name as object_name'
      'from user_tables'
      'where table_name not like '#39'CHART%'#39
      'and table_name not like '#39'WEB%'#39
      ' ')
    Left = 32
    Top = 256
    object llAnalyzerTablesTYPE: TStringField
      FieldName = 'TYPE'
      FixedChar = True
      Size = 5
    end
    object llAnalyzerTablesOBJECT_NAME: TStringField
      FieldName = 'OBJECT_NAME'
      Size = 30
    end
  end
  object calcLLChart: TStoredProc
    DatabaseName = 'llCheck_DB'
    StoredProcName = 'CALCCHART'
    Left = 112
    Top = 256
  end
  object llAnalyserCharts: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select '#39'table'#39' as type, table_name as object_name'
      'from user_tables'
      'where table_name like '#39'CHART%'#39
      'and table_name not like '#39'CHART_WEB%'#39
      'union'
      'select '#39'index'#39' as type, index_name as object_name'
      'from user_indexes'
      'where index_name like '#39'CHART%'#39
      'and index_name not like '#39'CHART_WEB%'#39
      ''
      ' ')
    Left = 184
    Top = 256
    object llAnalyserChartsTYPE: TStringField
      FieldName = 'TYPE'
      FixedChar = True
      Size = 5
    end
    object llAnalyserChartsOBJECT_NAME: TStringField
      FieldName = 'OBJECT_NAME'
      Size = 30
    end
  end
  object WebServerTable: TTable
    BeforeDelete = WebServerTableBeforeDelete
    DatabaseName = 'llCheck_DB'
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'SERVER_NAME'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'PATH'
        DataType = ftMemo
        Size = 1955
      end>
    IndexDefs = <
      item
        Name = 'SERVER_NAME_IDX'
        Fields = 'SERVER_NAME'
        Options = [ixUnique]
      end
      item
        Name = 'SYS_C002161'
        Fields = 'ID'
        Options = [ixUnique]
      end>
    StoreDefs = True
    TableName = 'WEB_SERVER'
    Left = 32
    Top = 328
    object WebServerTableID: TFloatField
      FieldName = 'ID'
      Required = True
    end
    object WebServerTableSERVER_NAME: TStringField
      DisplayLabel = 'Server Name'
      DisplayWidth = 32
      FieldName = 'SERVER_NAME'
      Size = 255
    end
    object WebServerTablePATH: TMemoField
      FieldName = 'PATH'
      Visible = False
      BlobType = ftMemo
      Size = 1955
    end
  end
  object webThreadTable: TTable
    OnCalcFields = webThreadTableCalcFields
    DatabaseName = 'llCheck_DB'
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'SERVER'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'REQUEST_DATE_TIME'
        Attributes = [faRequired]
        DataType = ftDateTime
      end
      item
        Name = 'HTTP_METHOD'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'HTTP_URL'
        Attributes = [faRequired]
        DataType = ftString
        Size = 255
      end
      item
        Name = 'HTTP_QUERY'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'HTTP_COOKIES'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'HTTP_AGENT'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'HTTP_STATUS'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'HTTP_SUB_STATUS'
        DataType = ftFloat
      end
      item
        Name = 'HTTP_WIN_STATUS'
        DataType = ftFloat
      end
      item
        Name = 'BYTES_RECEIVED'
        DataType = ftFloat
      end
      item
        Name = 'BYTES_SENT'
        DataType = ftFloat
      end
      item
        Name = 'EXEC_TIME'
        DataType = ftFloat
      end>
    IndexDefs = <
      item
        Name = 'FUNC_IDX'
        Fields = 'FUNC;EXEC_TIME'
      end
      item
        Name = 'REQUEST_DATE_IDX'
        Fields = 'REQUEST_DATE_TIME;SERVER;THREAD;START_TICK'
        Options = [ixUnique]
      end
      item
        Name = 'SERVER_IDX'
        Fields = 'SERVER'
      end
      item
        Name = 'SYS_C002197'
        Fields = 'ID'
        Options = [ixUnique]
      end
      item
        Name = 'TIME_IDX'
        Fields = 'EXEC_TIME'
      end>
    StoreDefs = True
    TableName = 'WEB_LOGS'
    Left = 144
    Top = 328
    object webThreadTableID: TFloatField
      FieldName = 'ID'
      Required = True
      Visible = False
    end
    object webThreadTableSERVER: TFloatField
      FieldName = 'SERVER'
      Required = True
      Visible = False
    end
    object webThreadTableSERVER_NAME: TStringField
      DisplayLabel = 'Server'
      FieldKind = fkLookup
      FieldName = 'SERVER_NAME'
      LookupDataSet = WebServerTable
      LookupKeyFields = 'ID'
      LookupResultField = 'SERVER_NAME'
      KeyFields = 'SERVER'
      Lookup = True
    end
    object webThreadTableREQUEST_DATE_TIME: TDateTimeField
      DisplayLabel = 'Date'
      FieldName = 'REQUEST_DATE_TIME'
      Required = True
    end
    object webThreadTableHTTP_METHOD: TStringField
      DisplayLabel = 'Method'
      DisplayWidth = 10
      FieldName = 'HTTP_METHOD'
      Size = 32
    end
    object webThreadTableHTTP_URL: TStringField
      DisplayLabel = 'URL'
      DisplayWidth = 32
      FieldName = 'HTTP_URL'
      Required = True
      Size = 255
    end
    object webThreadTableHTTP_QUERY: TStringField
      DisplayLabel = 'Query String'
      DisplayWidth = 46
      FieldName = 'HTTP_QUERY'
      Size = 255
    end
    object webThreadTableHTTP_COOKIES: TStringField
      DisplayLabel = 'Cookies'
      DisplayWidth = 32
      FieldName = 'HTTP_COOKIES'
      Size = 255
    end
    object webThreadTableHTTP_AGENT: TStringField
      DisplayLabel = 'Browser'
      DisplayWidth = 32
      FieldName = 'HTTP_AGENT'
      Size = 255
    end
    object webThreadTableHTTP_STATUS: TFloatField
      DisplayLabel = 'Status'
      DisplayWidth = 6
      FieldName = 'HTTP_STATUS'
      Required = True
    end
    object webThreadTableHTTP_SUB_STATUS: TFloatField
      DisplayLabel = 'Sub Status'
      FieldName = 'HTTP_SUB_STATUS'
    end
    object webThreadTableHTTP_WIN_STATUS: TFloatField
      DisplayLabel = 'Win Status'
      FieldName = 'HTTP_WIN_STATUS'
    end
    object webThreadTableBYTES_RECEIVED: TFloatField
      DisplayLabel = 'Bytes Rec.'
      FieldName = 'BYTES_RECEIVED'
    end
    object webThreadTableBYTES_SENT: TFloatField
      DisplayLabel = 'Bytes Sent'
      FieldName = 'BYTES_SENT'
    end
    object webThreadTableEXEC_TIME: TFloatField
      DisplayLabel = 'Exec. Time'
      FieldName = 'EXEC_TIME'
      Visible = False
    end
    object webThreadTableEXEC_SECS: TFloatField
      DisplayLabel = 'Exec. Time'
      FieldKind = fkCalculated
      FieldName = 'EXEC_SECS'
      Calculated = True
    end
  end
  object WebSummarizeServer: TStoredProc
    DatabaseName = 'llCheck_DB'
    StoredProcName = 'WEBSUMMARIZESERVER'
    Left = 32
    Top = 400
    ParamData = <
      item
        DataType = ftFloat
        Name = 'DAYSTOKEEP'
        ParamType = ptInput
      end
      item
        DataType = ftFloat
        Name = 'THESERVER'
        ParamType = ptInput
      end>
  end
  object webFunctionsTable: TTable
    DatabaseName = 'llCheck_DB'
    FieldDefs = <
      item
        Name = 'HTTP_URL'
        Attributes = [faRequired]
        DataType = ftString
        Size = 255
      end
      item
        Name = 'HTTP_QUERY'
        DataType = ftString
        Size = 255
      end>
    IndexDefs = <
      item
        Name = 'WEB_FUNCTIONS_IDX'
        Fields = 'HTTP_URL;HTTP_QUERY'
        Options = [ixUnique]
      end>
    IndexName = 'WEB_FUNCTIONS_IDX'
    StoreDefs = True
    TableName = 'WEB_FUNCTIONS'
    Left = 152
    Top = 400
    object webFunctionsTableHTTP_URL: TStringField
      FieldName = 'HTTP_URL'
      Required = True
      Size = 255
    end
    object webFunctionsTableHTTP_QUERY: TStringField
      FieldName = 'HTTP_QUERY'
      Size = 255
    end
  end
  object updateWebFunctionsQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'insert into WEB_FUNCTIONS'
      '('
      #9'HTTP_URL,'
      #9'HTTP_QUERY'
      ')'
      'select distinct lower(HTTP_URL), lower(HTTP_QUERY)'
      'from WEB_SUMMARY')
    Left = 272
    Top = 400
  end
  object calcWebChart: TStoredProc
    DatabaseName = 'llCheck_DB'
    StoredProcName = 'CALCWEBCHART'
    Left = 152
    Top = 472
  end
  object webAnalyzerTables: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select '#39'table'#39' as type, table_name as object_name'
      'from user_tables'
      'where table_name not like '#39'CHART%'#39
      'and table_name not like '#39'LL%'#39
      ' '
      ' ')
    Left = 40
    Top = 472
    object webAnalyzerTablesTYPE: TStringField
      FieldName = 'TYPE'
      FixedChar = True
      Size = 5
    end
    object webAnalyzerTablesOBJECT_NAME: TStringField
      FieldName = 'OBJECT_NAME'
      Size = 30
    end
  end
  object webAnalyserCharts: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select '#39'table'#39' as type, table_name as object_name'
      'from user_tables'
      'where table_name like '#39'CHART_WEB%'#39
      'union'
      'select '#39'index'#39' as type, index_name as object_name'
      'from user_indexes'
      'where index_name like '#39'CHART_WEB%'#39
      ''
      ' '
      ' ')
    Left = 240
    Top = 472
    object webAnalyserChartsTYPE: TStringField
      FieldName = 'TYPE'
      FixedChar = True
      Size = 5
    end
    object webAnalyserChartsOBJECT_NAME: TStringField
      FieldName = 'OBJECT_NAME'
      Size = 30
    end
  end
  object webSummarizeTable: TTable
    DatabaseName = 'llCheck_DB'
    FieldDefs = <
      item
        Name = 'SERVER'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'REQUEST_DATE_TIME'
        DataType = ftDateTime
      end
      item
        Name = 'HOUR'
        DataType = ftFloat
      end
      item
        Name = 'HTTP_URL'
        Attributes = [faRequired]
        DataType = ftString
        Size = 255
      end
      item
        Name = 'HTTP_QUERY'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'EXEC_TIME'
        DataType = ftFloat
      end
      item
        Name = 'NUM_REQUESTS'
        DataType = ftFloat
      end>
    IndexDefs = <
      item
        Name = 'WEB_REQUEST_DATE_IDX'
        Fields = 'SERVER;REQUEST_DATE_TIME;HOUR;HTTP_URL;HTTP_QUERY'
        Options = [ixUnique]
      end
      item
        Name = 'WEB_SUMMARY_IDX'
        Fields = 'REQUEST_DATE_TIME;HOUR'
      end>
    IndexName = 'WEB_SUMMARY_IDX'
    StoreDefs = True
    TableName = 'WEB_SUMMARY_TABLE'
    Left = 272
    Top = 328
    object webSummarizeTableSERVER: TFloatField
      DisplayLabel = 'ServerID'
      DisplayWidth = 8
      FieldName = 'SERVER'
      Required = True
      Visible = False
    end
    object webSummarizeTableSERVER_NAME: TStringField
      DisplayLabel = 'Server'
      FieldKind = fkLookup
      FieldName = 'SERVER_NAME'
      LookupDataSet = WebServerTable
      LookupKeyFields = 'ID'
      LookupResultField = 'SERVER_NAME'
      KeyFields = 'SERVER'
      Lookup = True
    end
    object webSummarizeTableREQUEST_DATE_TIME: TDateTimeField
      DisplayLabel = 'Date'
      DisplayWidth = 10
      FieldName = 'REQUEST_DATE_TIME'
    end
    object webSummarizeTableHOUR: TFloatField
      DisplayLabel = 'Hour'
      DisplayWidth = 4
      FieldName = 'HOUR'
    end
    object webSummarizeTableHTTP_URL: TStringField
      DisplayLabel = 'URL'
      DisplayWidth = 32
      FieldName = 'HTTP_URL'
      Required = True
      Size = 255
    end
    object webSummarizeTableHTTP_QUERY: TStringField
      DisplayLabel = 'Query String'
      DisplayWidth = 32
      FieldName = 'HTTP_QUERY'
      Size = 255
    end
    object webSummarizeTableEXEC_TIME: TFloatField
      DisplayLabel = 'Time'
      FieldName = 'EXEC_TIME'
    end
    object webSummarizeTableNUM_REQUESTS: TFloatField
      DisplayLabel = 'Count'
      FieldName = 'NUM_REQUESTS'
    end
  end
  object llSummarizeTable: TTable
    DatabaseName = 'llCheck_DB'
    FieldDefs = <
      item
        Name = 'SERVER'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'REQUEST_DATE_TIME'
        DataType = ftDateTime
      end
      item
        Name = 'HOUR'
        DataType = ftFloat
      end
      item
        Name = 'FUNC'
        Attributes = [faRequired]
        DataType = ftString
        Size = 255
      end
      item
        Name = 'OBJECT_ID'
        DataType = ftFloat
      end
      item
        Name = 'EXEC_TIME'
        DataType = ftFloat
      end
      item
        Name = 'SQL_TIME'
        DataType = ftFloat
      end
      item
        Name = 'GENERATE_TIME'
        DataType = ftFloat
      end
      item
        Name = 'NUM_REQUESTS'
        DataType = ftFloat
      end
      item
        Name = 'REQ_SQL_TIME'
        DataType = ftFloat
      end
      item
        Name = 'REQ_SQL_TIME_LOGED'
        DataType = ftFloat
      end
      item
        Name = 'REQ_SQL_COUNT'
        DataType = ftFloat
      end
      item
        Name = 'REC_FETCHED'
        DataType = ftFloat
      end
      item
        Name = 'REC_CHANGED'
        DataType = ftFloat
      end>
    IndexDefs = <
      item
        Name = 'LLTHREAD_SUMMARY_IDX'
        Fields = 'REQUEST_DATE_TIME;HOUR'
      end>
    IndexName = 'LLTHREAD_SUMMARY_IDX'
    StoreDefs = True
    TableName = 'LLTHREAD_SUMMARY_TABLE'
    Left = 224
    Top = 16
    object llSummarizeTableSERVER: TFloatField
      DisplayLabel = 'ServerID'
      DisplayWidth = 8
      FieldName = 'SERVER'
      Required = True
      Visible = False
    end
    object llSummarizeTableSERVER_NAME: TStringField
      DisplayLabel = 'Server'
      FieldKind = fkLookup
      FieldName = 'SERVER_NAME'
      LookupDataSet = ServerTable
      LookupKeyFields = 'ID'
      LookupResultField = 'SERVER_NAME'
      KeyFields = 'SERVER'
      Lookup = True
    end
    object llSummarizeTableREQUEST_DATE_TIME: TDateTimeField
      DisplayLabel = 'Date'
      DisplayWidth = 10
      FieldName = 'REQUEST_DATE_TIME'
    end
    object llSummarizeTableHOUR: TFloatField
      DisplayLabel = 'Hour'
      DisplayWidth = 4
      FieldName = 'HOUR'
    end
    object llSummarizeTableFUNC: TStringField
      DisplayLabel = 'Function'
      DisplayWidth = 40
      FieldName = 'FUNC'
      Required = True
      Size = 255
    end
    object llSummarizeTableOBJECT_ID: TFloatField
      DisplayLabel = 'ObjectID'
      FieldName = 'OBJECT_ID'
    end
    object llSummarizeTableEXEC_TIME: TFloatField
      DisplayLabel = 'Time'
      FieldName = 'EXEC_TIME'
    end
    object llSummarizeTableSQL_TIME: TFloatField
      DisplayLabel = 'SQL Time'
      FieldName = 'SQL_TIME'
    end
    object llSummarizeTableREQ_SQL_TIME: TFloatField
      DisplayLabel = 'Req. SQL Time'
      FieldName = 'REQ_SQL_TIME'
    end
    object llSummarizeTableREQ_SQL_TIME_LOGED: TFloatField
      DisplayLabel = 'Req. SQL Time Logged'
      FieldName = 'REQ_SQL_TIME_LOGED'
    end
    object llSummarizeTableREQ_SQL_COUNT: TFloatField
      DisplayLabel = 'Req. SQL Count'
      FieldName = 'REQ_SQL_COUNT'
    end
    object llSummarizeTableREC_FETCHED: TFloatField
      DisplayLabel = 'Rec. Fetched'
      FieldName = 'REC_FETCHED'
    end
    object llSummarizeTableREC_CHANGED: TFloatField
      DisplayLabel = 'Rec. Changed'
      FieldName = 'REC_CHANGED'
    end
    object llSummarizeTableNUM_REQUESTS: TFloatField
      DisplayLabel = 'Count'
      FieldName = 'NUM_REQUESTS'
    end
    object llSummarizeTableGENERATE_TIME: TFloatField
      DisplayLabel = 'Generate Time'
      FieldName = 'GENERATE_TIME'
    end
  end
end
