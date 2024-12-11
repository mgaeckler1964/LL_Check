object httpChartForm: ThttpChartForm
  Left = 661
  Top = 271
  Width = 792
  Height = 458
  Caption = 'HTTP Charts'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object theChart: TChart
    Left = 0
    Top = 65
    Width = 776
    Height = 354
    AllowZoom = False
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Foot.Visible = False
    Title.Text.Strings = (
      'TChart')
    Title.Visible = False
    Legend.Visible = False
    View3D = False
    Align = alClient
    TabOrder = 1
    object theSeries: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Title = 'DataSeries'
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object dbSeries: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clGreen
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object GenerateSeries: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clYellow
      Title = 'GenerateSeries'
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 776
    Height = 65
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 28
      Height = 13
      Caption = 'Chart:'
    end
    object Label2: TLabel
      Left = 296
      Top = 8
      Width = 26
      Height = 13
      Caption = 'Date:'
    end
    object funcLabel: TLabel
      Left = 8
      Top = 32
      Width = 43
      Height = 13
      Caption = 'Request:'
    end
    object funcComboBox: TComboBox
      Left = 56
      Top = 32
      Width = 577
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
    end
    object theDatePicker: TDateTimePicker
      Left = 344
      Top = 8
      Width = 137
      Height = 21
      CalAlignment = dtaLeft
      Date = 37328
      Time = 37328
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 1
    end
    object ModeComboBox: TComboBox
      Left = 56
      Top = 8
      Width = 233
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      Items.Strings = (
        'Average Time per Request and Hour/Day'
        'Average Time per Request and Hour'
        'Average Time per Request and User Count')
    end
    object CalcButton: TButton
      Left = 656
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Calc'
      TabOrder = 4
      OnClick = CalcButtonClick
    end
    object endDatePicker: TDateTimePicker
      Left = 496
      Top = 8
      Width = 137
      Height = 21
      CalAlignment = dtaLeft
      Date = 37328
      Time = 37328
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
    end
    object Complete: TCheckBox
      Left = 656
      Top = 40
      Width = 65
      Height = 17
      Caption = 'Complete'
      TabOrder = 5
    end
  end
  object funcQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select distinct lower(http_url)'
      'from http_thread'
      'order by 1')
    Left = 64
    Top = 40
  end
end
