using System.Windows;
using System.Windows.Documents;
using WPFWeather.Services;
using WPFWeather.ViewModels;

namespace WPFWeather.Windows
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            // Create ViewModel for weather download
            WeatherViewModel weather_vm = new WeatherViewModel(new WeatherDiskService());

            // Set Data Context before binding.
            DataContext = weather_vm;
        }
    }
}