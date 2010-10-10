{*
 * This file contains most of the code that implements a test
 * of the ZlibTool OCX.  It does this by compressing or decompressing
 * a selected file from an input list box.
 *}

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  OleCtrls, ZLIBTOOL, StdCtrls, FileCtrl;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Percent: TEdit;
    FileListBox1: TFileListBox;
    InputFile: TEdit;
    OutputFile: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Status: TEdit;
    Button2: TButton;
    Button3: TButton;
    Label4: TLabel;
    Button4: TButton;
    Label5: TLabel;
    Engine: TZlibToolCtrl;
    Level: TComboBox;
    procedure Button1Click(Sender: TObject);
    procedure EngineProgress(Sender: TObject; percent_complete: Smallint);
    procedure FileListBox1Change(Sender: TObject);
    procedure InputFileChange(Sender: TObject);
    procedure OutputFileChange(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure InputFileEnter(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure FormActivate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

{*
 * To compress, I just set the engine level to be the
 * currently selected level, then call the Compress()
 * method of the engine.  The input and output file
 * names are set when a file is selected from the
 * input list.
 *
 * Note that when the compression is done, I call the
 * Update() method of the file list box so that I will
 * see any newly created output files. I also take the
 * Zlib engine status and put it in a text box for the
 * user to see.
 *}

procedure TForm1.Button1Click(Sender: TObject);
begin
    Status.Text := 'Compressing...';
    Engine.Level := Level.ItemIndex;
    Button1.Enabled := false;
    Engine.Compress();
    Button1.Enabled := true;
    FileListBox1.Update();
    Status.Text := Engine.Status;
end;

{*
 * Decompression takes a nearly identical path as
 * compression.
 *}
procedure TForm1.Button2Click(Sender: TObject);
begin
    Status.Text := 'Decompressing...';
    Button2.Enabled := false;
    Engine.Decompress();
    Button2.Enabled := true;
    FileListBox1.Update();
    Status.Text := Engine.Status;
end;

{*
 * This procedure is bound to the Progress()
 * method of the engine.  It gest called
 * periodically during the compression process, with
 * a single numeric argument specifying the precent
 * of the input file that has been processed.  I
 * round the value off to the nearest five percent
 * and display it in a text box.
 *}

procedure TForm1.EngineProgress(Sender: TObject;
  percent_complete: Smallint);
begin
{ I round it off to the nearest 5% }
   percent_complete := percent_complete + 2;
   percent_complete := percent_complete div 5;
   percent_complete := percent_complete * 5;
   Percent.Text := IntToStr( percent_complete );
   Percent.Update();
end;

{*
 * Any time a new file is selected in the input list
 * box, I place it in the text box that indicates
 * which file will actually be either compressed or
 * decompressed.
 *}

procedure TForm1.FileListBox1Change(Sender: TObject);
begin
  if FileListBox1.ItemIndex >= 0 Then
    InputFile.Text := FileListBox1.Items[ FileListBox1.ItemIndex ];
end;

{*
 * When the input file name is changed, either by the user
 * typing in a new name, or by the user selecting a file
 * name from the list box, this routine gets called.  It
 * sets the engine property, then gets the resulting output
 * file name from the engine. If you input a name like
 * foo.dat.ZL, the output name will be foo.dat.  If you input
 * a name like foo.dat, the output name will be foo.dat.ZL.
 * This is the way the OCX works, it has nothing to do with
 * the way Zlib works.
 *}

procedure TForm1.InputFileChange(Sender: TObject);
begin
  Engine.InputFile := InputFile.Text;
  OutputFile.Text := Engine.OutputFile;
end;

{*
 * When the user types in a new output file name,
 * we are sure to copy it to the engine output file
 * name property.
 *}

procedure TForm1.OutputFileChange(Sender: TObject);
begin
  Engine.OutputFile := OutputFile.Text;
end;

{*
 * Exit the program.  Maybe it would be a good
 * idea to disable this button while the
 * compression or decompression process is running.
 *}
procedure TForm1.Button3Click(Sender: TObject);
begin
  Close();
end;

{*
 * When a new input file is selected, I jump over
 * to the file list box.
 *}

procedure TForm1.InputFileEnter(Sender: TObject);
begin
   FileListBox1.SetFocus();
end;

{*
 * Being able to abort the compression process is
 * a really good thing.  When this button is clicked,
 * the abort method is invoked.  Since the engine is
 * periodically servicing the message loop, this
 * should eventually be noticed, and the compression
 * aborted.
 *}
procedure TForm1.Button4Click(Sender: TObject);
begin
    Engine.Abort();
end;

{*
 * When the form is first activated, I set the compression
 * level to the default value selected by the compression
 * engine.
 *}

procedure TForm1.FormActivate(Sender: TObject);
begin
    Level.ItemIndex := Engine.Level;
end;

end.
