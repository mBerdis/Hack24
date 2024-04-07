using CookBook.App.ViewModels;
using Microsoft.Maui.Controls;

namespace CookBook.App.Views.Template;

public partial class TemplateListView : ContentPageBase
{
    public TemplateListView(TemplateListViewModel viewModel)
        : base(viewModel)
    {
        InitializeComponent();
    }
}
