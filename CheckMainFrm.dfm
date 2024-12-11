object CheckMainForm: TCheckMainForm
  Left = 357
  Top = 275
  Width = 658
  Height = 263
  Caption = 'LL Check'
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
    Left = 32
    Top = 56
    object File1: TMenuItem
      Caption = '&File'
      object DeleteoldEntries: TMenuItem
        Caption = '&Delete old Entries...'
        OnClick = DeleteoldEntriesClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit: TMenuItem
        Caption = 'E&xit'
        OnClick = ExitClick
      end
    end
    object View1: TMenuItem
      Caption = '&View/Tests'
      object LLServers: TMenuItem
        Caption = 'LL Servers...'
        OnClick = LLServersClick
      end
      object Livelink1: TMenuItem
        Caption = 'LL Threads'
        OnClick = Livelink1Click
      end
      object LLSummarizeView: TMenuItem
        Caption = 'LL Summarize View'
        OnClick = LLSummarizeViewClick
      end
      object LLStatistics: TMenuItem
        Caption = 'LL Statistics'
        OnClick = LLStatisticsClick
      end
      object LLCharts: TMenuItem
        Caption = 'LL Charts'
        OnClick = LLChartsClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object HTTP1: TMenuItem
        Caption = 'HTTP'
        OnClick = HTTP1Click
      end
      object HTTPTimes1: TMenuItem
        Caption = 'HTTP Times'
        OnClick = HTTPTimes1Click
      end
      object HTTPCharts1: TMenuItem
        Caption = 'HTTP Charts'
        OnClick = HTTPCharts1Click
      end
      object HTTPAutochecks1: TMenuItem
        Caption = 'HTTP Autochecks'
        OnClick = HTTPAutochecks1Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object WebServers: TMenuItem
        Caption = 'Web Servers...'
        OnClick = WebServersClick
      end
      object WebRequests: TMenuItem
        Caption = 'Web Requests'
        OnClick = WebRequestsClick
      end
      object WebSummarizeView: TMenuItem
        Caption = 'Web Summarize View'
        OnClick = WebSummarizeViewClick
      end
      object WebStatistics: TMenuItem
        Caption = 'Web Statistics'
        OnClick = WebStatisticsClick
      end
      object WebCharts: TMenuItem
        Caption = 'Web Charts'
        OnClick = WebChartsClick
      end
      object N5: TMenuItem
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
