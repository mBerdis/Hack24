// Copyright (c) .NET Foundation and contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

using System.Diagnostics;
using CookBook.App.ViewModels;
using NAudio.Wave;

namespace CookBook.App;

public class Mp3Convertor
{
    private static int noteCount = 134;


    public static void Mp3ToMelody(string filename)
    {
        // Set up the process start info
        using (var reader = new AudioFileReader(filename))
        {
            int bytesPerSample = reader.WaveFormat.BitsPerSample / 8;
            int channels = reader.WaveFormat.Channels;
            int sampleRate = reader.WaveFormat.SampleRate;

            // Read all samples
            byte[] buffer = new byte[reader.Length];
            int read = reader.Read(buffer, 0, buffer.Length);

            // Convert byte array to float array
            float[] samples = new float[read / bytesPerSample / channels];
            for (int i = 0; i < samples.Length; i++)
            {
                samples[i] = BitConverter.ToInt16(buffer, i * bytesPerSample * channels) / (float)short.MaxValue;
            }

            // Downsample
            int targetSamplingFreq = 250;
            int downsampleFactor = (int)Math.Round((double)sampleRate / targetSamplingFreq);
            float[] downsampledSamples = new float[samples.Length / downsampleFactor];
            for (int i = 0; i < downsampledSamples.Length; i++)
            {
                downsampledSamples[i] = samples[i * downsampleFactor];
            }

            // Rescale
            float minimum = downsampledSamples.Min();
            float maximum = downsampledSamples.Max();
            float desiredMax = noteCount / maximum;
            for (int i = 0; i < downsampledSamples.Length; i++)
            {
                downsampledSamples[i] *= desiredMax;
            }

            // Round and print
            for (int i = 0; i < downsampledSamples.Length; i++)
            {
                if (downsampledSamples[i] > 0 && downsampledSamples[i] <= noteCount)
                {
                    byte byteRepresentation = (byte)Math.Round(downsampledSamples[i]);
                    TemplateDetailViewModel.send_via_serial(byteRepresentation);
                    Thread.Sleep(12);
                }
            }
        }

        TemplateDetailViewModel.send_via_serial(255);
    }
}
/*ProcessStartInfo start = new ProcessStartInfo();
        start.FileName = "python3.10"; // The path to your Python interpreter
        start.Arguments = "C:\\Users\\samod\\Desktop\\skola\\2BIT\\Graph\\convertor.py "; // Path to your Python script
        start.Arguments += filename;
        start.UseShellExecute = false;
        start.RedirectStandardOutput = true;
        start.CreateNoWindow = true;

        Console.WriteLine(start.Arguments);

        // Start the process
        using (Process process = Process.Start(start))
        {
            // Read the output of the Python program
            using (StreamReader reader = process.StandardOutput)
            {
                while (!reader.EndOfStream)
                {
                    int nextByte = reader.Read();
                    if (nextByte >= 0)
                    {
                        byte nextChar = (byte)nextByte;
                        TemplateDetailViewModel.send_via_serial(nextChar);
                    }
                    else
                    {
                        break; // Break out of the loop if the end of the stream is reached
                    }
                }
            }
        }*/
