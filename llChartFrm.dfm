object LLChartForm: TLLChartForm
  Left = 429
  Top = 377
  Width = 995
  Height = 743
  Caption = 'LL Charts'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefaultPosOnly
  Visible = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object theChart: TChart
    Left = 0
    Top = 65
    Width = 979
    Height = 564
    AllowZoom = False
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Foot.Visible = False
    Title.Text.Strings = (
      'TChart')
    Title.Visible = False
    Legend.Color = clSilver
    Legend.ColorWidth = 100
    Legend.DividingLines.Width = 5
    Legend.LegendStyle = lsSeries
    Legend.ShadowSize = 0
    Legend.TextStyle = ltsPlain
    View3D = False
    Align = alClient
    TabOrder = 1
  end
  object PanelControl: TPanel
    Left = 0
    Top = 0
    Width = 979
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
    object ServerLabel: TLabel
      Left = 8
      Top = 32
      Width = 34
      Height = 13
      Caption = 'Server:'
    end
    object funcLabel: TLabel
      Left = 296
      Top = 32
      Width = 43
      Height = 13
      Caption = 'Request:'
    end
    object RoundLabel: TLabel
      Left = 536
      Top = 32
      Width = 35
      Height = 13
      Caption = 'Round:'
    end
    object LabelMinRequests: TLabel
      Left = 640
      Top = 32
      Width = 27
      Height = 13
      Caption = 'Min#:'
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
      DropDownCount = 12
      ItemHeight = 13
      TabOrder = 0
      OnChange = ModeComboBoxChange
      Items.Strings = (
        'Time per Request'
        'Average Time per Request and Hour'
        'Average Time per Request and Day'
        'Total Time per Hour'
        'Total Time per Hour and Day'
        'Total Time per Hour and Server'
        'Analyze'
        'Average Requests per Hour'
        'Requests per Day'
        'Requests per Day and Server'
        'Usage per Hour'
        'Usage per Day')
    end
    object serverComboBox: TComboBox
      Left = 56
      Top = 32
      Width = 233
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
    end
    object CalcButton: TButton
      Left = 752
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Calc'
      TabOrder = 7
      OnClick = CalcButtonClick
    end
    object roundUpDown: TUpDown
      Left = 617
      Top = 32
      Width = 15
      Height = 21
      Associate = roundEdit
      Min = 0
      Max = 3
      Position = 0
      TabOrder = 6
      Wrap = False
    end
    object roundEdit: TEdit
      Left = 576
      Top = 32
      Width = 41
      Height = 21
      TabOrder = 5
      Text = '0'
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
    object funcDBEdit: TDBEdit
      Left = 344
      Top = 32
      Width = 137
      Height = 21
      DataField = 'FUNC_ID'
      DataSource = funcSource
      TabOrder = 4
    end
    object SelectRequestButton: TButton
      Left = 752
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Sel. Requ.'
      TabOrder = 8
      OnClick = SelectRequestButtonClick
    end
    object EditMinRequests: TEdit
      Left = 680
      Top = 32
      Width = 41
      Height = 21
      TabOrder = 9
      Text = '0'
    end
    object UpDownMinRequests: TUpDown
      Left = 721
      Top = 32
      Width = 15
      Height = 21
      Associate = EditMinRequests
      Min = 0
      Max = 32767
      Position = 0
      TabOrder = 10
      Wrap = False
    end
    object CheckBoxSizer: TCheckBox
      Left = 840
      Top = 16
      Width = 97
      Height = 17
      Caption = 'Sizer'
      Checked = True
      State = cbChecked
      TabOrder = 11
      OnClick = CheckBoxSizerClick
    end
    object CheckBoxLegend: TCheckBox
      Left = 840
      Top = 40
      Width = 97
      Height = 17
      Caption = 'Legend'
      Checked = True
      State = cbChecked
      TabOrder = 12
      OnClick = CheckBoxLegendClick
    end
  end
  object PanelSizer: TPanel
    Left = 0
    Top = 629
    Width = 979
    Height = 75
    Align = alBottom
    TabOrder = 2
    object ScrollBar: TScrollBar
      Left = 8
      Top = 48
      Width = 971
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      Max = 0
      PageSize = 1
      TabOrder = 0
      OnChange = ScrollBarChange
    end
    object TrackBar: TTrackBar
      Left = 8
      Top = 8
      Width = 971
      Height = 33
      Anchors = [akLeft, akTop, akRight]
      Max = 100
      Min = 1
      Orientation = trHorizontal
      Frequency = 1
      Position = 1
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = TrackBarChange
    end
  end
  object funcQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select distinct'
      
        #9'substr( lower(func) || '#39'('#39'  || to_char(object_id) || '#39')'#39', 1, 25' +
        '5 ) as func_id,'
      #9'func,'
      #9'object_id'
      'from llthread_functions'
      'where func like :theFunc'
      'and to_char(object_id) like :theObjId'
      ' '
      ' ')
    Left = 384
    Top = 64
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'theFunc'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'theObjId'
        ParamType = ptUnknown
      end>
  end
  object serverQuery: TQuery
    DatabaseName = 'llCheck_DB'
    SQL.Strings = (
      'select distinct server_name'
      'from server')
    Left = 56
    Top = 32
  end
  object funcSource: TDataSource
    DataSet = funcQuery
    Left = 440
    Top = 65
  end
end
