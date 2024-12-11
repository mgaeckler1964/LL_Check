object LLStatChartForm: TLLStatChartForm
  Left = 353
  Top = 409
  Width = 756
  Height = 538
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'LL Statistics Chart'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object theChart: TChart
    Left = 0
    Top = 41
    Width = 748
    Height = 470
    AllowPanning = pmNone
    AllowZoom = False
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    BackWall.Pen.Visible = False
    MarginBottom = 0
    MarginLeft = 0
    MarginRight = 0
    MarginTop = 0
    Title.Text.Strings = (
      'Statistics')
    Title.Visible = False
    AxisVisible = False
    Chart3DPercent = 10
    ClipPoints = False
    Frame.Visible = False
    Legend.Alignment = laLeft
    Legend.TextStyle = ltsLeftPercent
    Legend.Visible = False
    View3DOptions.Elevation = 315
    View3DOptions.Orthogonal = False
    View3DOptions.Perspective = 0
    View3DOptions.Rotation = 360
    View3DWalls = False
    Align = alClient
    TabOrder = 0
    AutoSize = True
    object dbSeries: TPieSeries
      Marks.ArrowLength = 0
      Marks.Style = smsLabelPercent
      Marks.Visible = True
      SeriesColor = clRed
      Title = 'dbSeries'
      Circled = True
      OtherSlice.Style = poBelowPercent
      OtherSlice.Text = 'Other'
      OtherSlice.Value = 5
      PieValues.DateTime = False
      PieValues.Name = 'Pie'
      PieValues.Multiplier = 1
      PieValues.Order = loAscending
    end
  end
  object ControlPanel: TPanel
    Left = 0
    Top = 0
    Width = 748
    Height = 41
    Align = alTop
    TabOrder = 1
    object Label1: TLabel
      Left = 144
      Top = 12
      Width = 50
      Height = 13
      Caption = 'Threshold:'
    end
    object Count: TRadioButton
      Left = 8
      Top = 11
      Width = 65
      Height = 17
      Caption = 'Count'
      TabOrder = 0
      OnClick = reloadData
    end
    object TotalTime: TRadioButton
      Left = 64
      Top = 11
      Width = 81
      Height = 17
      Caption = 'Total Time'
      TabOrder = 1
      OnClick = reloadData
    end
    object Edit1: TEdit
      Left = 200
      Top = 8
      Width = 33
      Height = 21
      TabOrder = 2
      Text = '5'
    end
    object UpDown1: TUpDown
      Left = 233
      Top = 8
      Width = 15
      Height = 21
      Associate = Edit1
      Min = 0
      Position = 5
      TabOrder = 3
      Wrap = False
      OnChangingEx = UpDown1ChangingEx
    end
  end
end
