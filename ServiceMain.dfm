object httpCheckService: ThttpCheckService
  OldCreateOrder = False
  AllowPause = False
  DisplayName = 'CRESD HTTP Check'
  OnShutdown = ServiceShutdown
  OnStart = ServiceStart
  OnStop = ServiceStop
  Left = 358
  Top = 116
  Height = 473
  Width = 610
  object llCheckDatabase: TDatabase
    AliasName = 'LL_CHECK'
    DatabaseName = 'llCheckDB'
    LoginPrompt = False
    Params.Strings = (
      'USER NAME=LL_CHECK'
      'PASSWORD=LL_CHECK')
    SessionName = 'Default'
    Left = 40
    Top = 24
  end
  object TableHttpRecurring: TTable
    AutoRefresh = True
    DatabaseName = 'llCheckDB'
    IndexName = 'HTTP_RECURRING_IDX'
    TableName = 'HTTP_RECURRING'
    UpdateMode = upWhereKeyOnly
    Left = 136
    Top = 24
    object TableHttpRecurringID: TFloatField
      AutoGenerateValue = arAutoInc
      FieldName = 'ID'
      Required = True
    end
    object TableHttpRecurringHTTP_URL: TMemoField
      FieldName = 'HTTP_URL'
      Required = True
      BlobType = ftMemo
      Size = 1995
    end
    object TableHttpRecurringHTTP_COOKIES: TMemoField
      FieldName = 'HTTP_COOKIES'
      BlobType = ftMemo
      Size = 1995
    end
    object TableHttpRecurringPROXY_SERVER: TStringField
      FieldName = 'PROXY_SERVER'
      Size = 255
    end
    object TableHttpRecurringPROXY_PORT: TFloatField
      FieldName = 'PROXY_PORT'
    end
    object TableHttpRecurringINTERVAL: TFloatField
      FieldName = 'INTERVAL'
      Required = True
    end
    object TableHttpRecurringNEXT_START: TDateTimeField
      FieldName = 'NEXT_START'
    end
    object TableHttpRecurringMAX_TIME: TFloatField
      FieldName = 'MAX_TIME'
      Required = True
    end
    object TableHttpRecurringLAST_TIME: TFloatField
      FieldName = 'LAST_TIME'
    end
    object TableHttpRecurringLAST_STATUS: TFloatField
      FieldName = 'LAST_STATUS'
    end
    object TableHttpRecurringE_MAIL_ALERT: TStringField
      FieldName = 'E_MAIL_ALERT'
      Size = 255
    end
    object TableHttpRecurringSMTP_SERVER: TStringField
      FieldName = 'SMTP_SERVER'
      Size = 255
    end
    object TableHttpRecurringSMTP_PORT: TFloatField
      FieldName = 'SMTP_PORT'
    end
    object TableHttpRecurringSMTP_USER: TStringField
      FieldName = 'SMTP_USER'
      Size = 255
    end
  end
  object NMSMTP: TNMSMTP
    Port = 25
    ReportLevel = 0
    OnInvalidHost = NMSMTPInvalidHost
    OnConnectionFailed = NMSMTPConnectionFailed
    EncodeType = uuMime
    ClearParams = True
    SubType = mtPlain
    Charset = 'us-ascii'
    OnRecipientNotFound = NMSMTPRecipientNotFound
    OnFailure = NMSMTPFailure
    OnAuthenticationFailed = NMSMTPAuthenticationFailed
    Left = 32
    Top = 96
  end
  object TableHTTP_THREAD: TTable
    AutoCalcFields = False
    AutoRefresh = True
    DatabaseName = 'llCheckDB'
    TableName = 'HTTP_THREAD'
    UpdateMode = upWhereKeyOnly
    Left = 144
    Top = 104
    object TableHTTP_THREADID: TFloatField
      AutoGenerateValue = arAutoInc
      FieldName = 'ID'
    end
    object TableHTTP_THREADHTTP_URL: TMemoField
      FieldName = 'HTTP_URL'
      Required = True
      BlobType = ftMemo
      Size = 1995
    end
    object TableHTTP_THREADHTTP_COOKIES: TMemoField
      FieldName = 'HTTP_COOKIES'
      BlobType = ftMemo
      Size = 1995
    end
    object TableHTTP_THREADREQUEST_DATE_TIME: TDateTimeField
      AutoGenerateValue = arDefault
      FieldName = 'REQUEST_DATE_TIME'
      Required = True
    end
    object TableHTTP_THREADLOOP_COUNT: TFloatField
      FieldName = 'LOOP_COUNT'
      Required = True
    end
    object TableHTTP_THREADUSER_COUNT: TFloatField
      FieldName = 'USER_COUNT'
      Required = True
    end
    object TableHTTP_THREADAVG_TIME: TFloatField
      FieldName = 'AVG_TIME'
    end
    object TableHTTP_THREADPROXY_SERVER: TStringField
      FieldName = 'PROXY_SERVER'
      Size = 255
    end
    object TableHTTP_THREADPROXY_PORT: TFloatField
      FieldName = 'PROXY_PORT'
    end
    object TableHTTP_THREADCOMPLETE_FLAG: TStringField
      FieldName = 'COMPLETE_FLAG'
      Size = 1
    end
    object TableHTTP_THREADLINK_CHECK: TStringField
      FieldName = 'LINK_CHECK'
      Size = 1
    end
    object TableHTTP_THREADTOTAL_SIZE: TFloatField
      FieldName = 'TOTAL_SIZE'
    end
    object TableHTTP_THREADNUM_FILES: TFloatField
      FieldName = 'NUM_FILES'
    end
    object TableHTTP_THREADMAX_FILES: TFloatField
      FieldName = 'MAX_FILES'
    end
  end
end
