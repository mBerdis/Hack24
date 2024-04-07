using System.Diagnostics;
using System.Speech.Synthesis;
using AudioTools.Implementation;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using CookBook.App.Messages;
using CookBook.App.Services;
using CookBook.BL.Facades;
using CookBook.BL.Facades.Interfaces;
using CookBook.BL.Models;
using CookBook.Common.Enums;
using NAudio.Lame;
using NAudio.Wave;

namespace CookBook.App.ViewModels;


public partial class TemplateEditViewModel(

    INavigationService navigationService,
    IMessengerService messengerService)
    : ViewModelBase(messengerService), IRecipient<TemplateEditMessage>, IRecipient<TemplateAddMessage>,
        IRecipient<TemplateDeleteMessage>
{
    public FileResult? PickedFile{ get; set; }
    public string? TTSinput { get; set; }


    protected override async Task LoadDataAsync()
    {
        await base.LoadDataAsync();
    }

    [RelayCommand]
    private async Task GenerateToPiezoAsync()
    {
        Mp3Convertor.Mp3ToMelody(PickedFile?.FullPath);
    }

    private void GenerateTTS()
    {
        string speechText = TTSinput;
        string wavOutputPath = Path.GetFullPath("temp.wav");
        string mp3OutputPath = Path.GetFullPath("temp.mp3");

        using (SpeechSynthesizer reader = new SpeechSynthesizer()) {
            //set some settings
            reader.Volume = 100;
            reader.Rate = 0; //medium

            //save to memory stream
            MemoryStream ms = new MemoryStream();
            reader.SetOutputToWaveStream(ms);

            //do speaking
            reader.Speak(speechText);

            //now convert to mp3 using LameEncoder or shell out to audiograbber
            ConvertWavStreamToMp3File(ref ms, mp3OutputPath);
        }

        // Call the Mp3ToMelody method
        Mp3Convertor.Mp3ToMelody(mp3OutputPath);
    }

    public static void ConvertWavStreamToMp3File(ref MemoryStream ms, string savetofilename) {
        //rewind to beginning of stream
        ms.Seek(0, SeekOrigin.Begin);

        using (var retMs = new MemoryStream())
        using (var rdr = new WaveFileReader(ms))
        using (var wtr = new LameMP3FileWriter(savetofilename, rdr.WaveFormat, LAMEPreset.VBR_90)) {
            rdr.CopyTo(wtr);
        }
    }

    [RelayCommand]
    private async Task SendTTSAsync()
    {
        GenerateTTS();
    }

    public async void Receive(TemplateEditMessage message)
    {
        await ReloadDataAsync();
    }

    public async void Receive(TemplateAddMessage message)
    {
        await ReloadDataAsync();
    }

    public async void Receive(TemplateDeleteMessage message)
    {
        await ReloadDataAsync();
    }

    private async Task ReloadDataAsync()
    {

    }
    [RelayCommand]
    private async Task PickFileAsync(PickOptions options)
    {

        try
        {
            PickedFile = await FilePicker.Default.PickAsync(options);
            if (PickedFile != null)
            {
                if (!PickedFile.FileName.EndsWith("mp3", StringComparison.OrdinalIgnoreCase))
                {
                    PickedFile = null;
                }
            }
        }
        catch (Exception ex)
        {
            // The user canceled or something went wrong
        }
    }
}
