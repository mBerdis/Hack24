using CommunityToolkit.Mvvm.Input;
using CookBook.App.Services;
using CookBook.App.ViewModels;

namespace CookBook.App.Shells;

public partial class AppShell
{
    private readonly INavigationService _navigationService;

    public AppShell(INavigationService navigationService)
    {
        _navigationService = navigationService;

        InitializeComponent();
    }

    [RelayCommand]
    private async Task GoToTemplatesAsync()
        => await _navigationService.GoToAsync<TemplateListViewModel>();
}
