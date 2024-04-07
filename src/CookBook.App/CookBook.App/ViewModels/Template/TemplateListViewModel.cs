using System.IO.Ports;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using CookBook.App.Messages;
using CookBook.App.Services;
using CookBook.BL.Facades;
using CookBook.BL.Facades.Interfaces;
using CookBook.BL.Models;

namespace CookBook.App.ViewModels;

public partial class TemplateListViewModel(
    ITemplateFacade templateFacade,
    INavigationService navigationService,
    IMessengerService messengerService)
    : ViewModelBase(messengerService), IRecipient<TemplateEditMessage>, IRecipient<TemplateDeleteMessage>
{
    public IEnumerable<TemplateListModel> Templates { get; set; } = null!;


    protected override async Task LoadDataAsync()
    {
        await base.LoadDataAsync();

        Templates = await templateFacade.GetAsync();

    }

    [RelayCommand]
    private async Task GoToPianoAsync()
    {


        await navigationService.GoToAsync("/piano");
    }
    [RelayCommand]
    private async Task GoToMusicConverterAsync()
    {

        await navigationService.GoToAsync("/musicConverter");
    }

 [RelayCommand]
    private async Task GoToCreateAsync()
    {
        await navigationService.GoToAsync("/edit");
    }

    public async void Receive(TemplateEditMessage message)
    {
        await LoadDataAsync();
    }

    public async void Receive(TemplateDeleteMessage message)
    {
        await LoadDataAsync();
    }
}
