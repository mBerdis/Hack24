using CookBook.App.ViewModels;
using Microsoft.Maui.Controls;

namespace CookBook.App.Views.Template;

public partial class TemplateEditView : ContentPageBase
{
    public TemplateEditView(TemplateEditViewModel viewModel)
        : base(viewModel)
    {
        InitializeComponent();
    }
}
