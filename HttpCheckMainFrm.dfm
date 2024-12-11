object HttpCheckMainForm: THttpCheckMainForm
  Left = 396
  Top = 610
  Width = 658
  Height = 263
  Caption = 'HTTP Check'
  Color = clAppWorkSpace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu
  OldCreateOrder = False
  Position = poDefault
  WindowMenu = Windows1
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu: TMainMenu
    Left = 192
    Top = 8
    object File1: TMenuItem
      Caption = '&File'
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
      end
    end
    object View1: TMenuItem
      Caption = '&View/Tests'
      object HTTP1: TMenuItem
        Caption = 'HTTP'
        OnClick = HTTP1Click
      end
      object HTTPTimes: TMenuItem
        Caption = 'HTTP Times'
        OnClick = HTTPTimesClick
      end
      object HTTPCharts: TMenuItem
        Caption = 'HTTP Charts'
        OnClick = HTTPChartsClick
      end
      object HTTPAutochecks: TMenuItem
        Caption = 'HTTP Autochecks'
        OnClick = HTTPAutochecksClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object WebTests: TMenuItem
        Caption = 'Web Tests'
        OnClick = WebTestsClick
      end
    end
    object Windows1: TMenuItem
      Caption = '&Windows'
      object ArrangeVertical1: TMenuItem
        Caption = 'Arrange &Vertical'
        OnClick = ArrangeVertical1Click
      end
      object ArrangeHorizontal1: TMenuItem
        Caption = 'Arrange &Horizontal'
        OnClick = ArrangeHorizontal1Click
      end
      object Cascade1: TMenuItem
        Caption = '&Cascade'
        OnClick = Cascade1Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
    end
    object Info1: TMenuItem
      Caption = 'Info!'
      OnClick = Info1Click
    end
  end
end
