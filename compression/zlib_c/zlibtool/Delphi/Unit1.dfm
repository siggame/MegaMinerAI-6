�
 TFORM1 00  TPF0TForm1Form1Left� ToplWidth�HeightaCaptionZLIB OCX Test Program
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.Style 
OnActivateFormActivatePixelsPerInch`
TextHeight TLabelLabel1Left� Top`Width.HeightCaptionInput File:  TLabelLabel2Left� Top� Width6HeightCaptionOutput File:  TLabelLabel3Left� Top@WidthWHeightCaptionPercent Complete:  TLabelLabel4Left+TopWidthAHeight)	AlignmenttaCenterAutoSizeCaptionZSelect an uncompressed file to compress to a Zlib file, or select a ZL file to decompress.
Font.ColorclBlackFont.Height�	Font.NameMS Sans Serif
Font.StylefsBold 
ParentFont  TLabelLabel5Left� Top� WidthEHeightCaptionEngine Status:  TButtonButton1LeftTopWidthYHeight!Caption	&CompressTabOrder OnClickButton1Click  TEditPercentLeft� Top@Width� HeightTabStopTabOrderOnEnterInputFileEnter  TFileListBoxFileListBox1LeftTop8WidthqHeight� 
ItemHeightTabOrderOnChangeFileListBox1Change  TEdit	InputFileLeft� Top`Width� HeightTabStopReadOnly	TabOrderOnChangeInputFileChangeOnEnterInputFileEnter  TEdit
OutputFileLeft� Top� Width� HeightTabStopReadOnly	TabOrderOnChangeOutputFileChangeOnEnterInputFileEnter  TEditStatusLeft� Top� Width� HeightTabStopTabOrderOnChangeOutputFileChangeOnEnterInputFileEnter  TButtonButton2LeftpTopWidthYHeight!Caption&DecompressTabOrderOnClickButton2Click  TButtonButton3Left0TopWidthYHeight!CaptionE&xitTabOrderOnClickButton3Click  TButtonButton4Left� TopWidthYHeight!Caption&AbortTabOrderOnClickButton4Click  TZlibToolCtrlEngineLeftKTop� WidthHeightTabOrder	
OnProgressEngineProgressControlData
      �  �               	TComboBoxLevelLeft� Top� Width� HeightStylecsDropDownList
ItemHeightItems.Strings0 - No compression1 - Fastest2 -3 - Fast4 - 5 -6 - Standard7 -8 -9 - Maximum TabOrder
   