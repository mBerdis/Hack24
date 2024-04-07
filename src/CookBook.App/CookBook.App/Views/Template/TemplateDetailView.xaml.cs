using CookBook.App.ViewModels;
using Microsoft.Maui.Controls;
using System.Diagnostics;
using ABI.Microsoft.UI.Xaml;

namespace CookBook.App.Views.Template;

public partial class TemplateDetailView : ContentPageBase
{
    private Stopwatch stopwatch;
    public List<byte> tones;
    public List<long> durations;
    public TemplateDetailView(TemplateDetailViewModel viewModel)
        : base(viewModel)
    {
        stopwatch = new Stopwatch();
        tones = new List<byte>();
        durations = new List<long>();
        InitializeComponent();
    }

    // Define the event handler for the button press
    private void OnButtonPressed(object sender, EventArgs e)
    {
        // Retrieve the button
        var button = sender as Button;

        // Retrieve the command parameter
        string parameter = button.CommandParameter as string;
        stopwatch.Reset();
        stopwatch.Start();
        tones.Add((byte)(Convert.ToByte(parameter) * 3));
        TemplateDetailViewModel.send_via_serial((byte)(Convert.ToByte(parameter) * 3));
    }

    private void OnButtonReleased(object sender, EventArgs e)
    {
        stopwatch.Stop();
        durations.Add(stopwatch.ElapsedMilliseconds);
        TemplateDetailViewModel.send_via_serial(255);
    }

    private void SaveSong(object sender, EventArgs e)
    {
        var writer = new StreamWriter("myFirstSong.mfs");

        for (int i = 0; i < tones.Count; i++)
        {
            string binaryString = Convert.ToString(tones[i], 2).PadLeft(8, '0');
            writer.Write(binaryString + ',');
            if (durations.Count < i)
            {
                writer.Write(durations[i]);
            }
            else
            {
                writer.Write(100);
            }
        }
        writer.Close();
        durations.Clear();
        tones.Clear();
    }

}
