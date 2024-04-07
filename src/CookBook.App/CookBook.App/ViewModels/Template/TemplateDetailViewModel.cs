using System.Collections.Generic;
using System.IO.Ports;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using CookBook.App.Messages;
using CookBook.App.Services;
using CookBook.BL.Facades;
using CookBook.BL.Facades.Interfaces;
using CookBook.BL.Models;

namespace CookBook.App.ViewModels;

public partial class TemplateDetailViewModel(
    INavigationService navigationService,
    IMessengerService messengerService)
    : ViewModelBase(messengerService), IRecipient<TemplateEditMessage>, IRecipient<TemplateAddMessage>,
        IRecipient<TemplateDeleteMessage>
{
    public static SerialPort serialPort = new SerialPort("COM5", 9600); // Change COM5 to your Arduino's COM port

    protected override async Task LoadDataAsync()
    {
        await base.LoadDataAsync();
    }


    [RelayCommand]
    private async Task PlayAsync(string note)
    {
        send_via_serial((byte)(Byte.Parse(note) * 3));
        //await navigationService.GoToAsync("/piano");
    }

    public async void Receive(TemplateEditMessage message)
    {

    }

    public async void Receive(TemplateAddMessage message)
    {
        await LoadDataAsync();
    }

    public async void Receive(TemplateDeleteMessage message)
    {
        await LoadDataAsync();
    }

    public static void send_via_serial(byte index)
    {
        try
        {
            serialPort.Open();
            serialPort.Write(new byte[] { index }, 0, 1);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error opening serial port: {ex.Message}");
        }
        finally
        {
            serialPort.Close();
        }
    }
}
