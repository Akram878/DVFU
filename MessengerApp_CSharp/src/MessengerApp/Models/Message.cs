namespace MessengerApp.Models;

/// <summary>
/// Abstract base message supporting polymorphism across different message types.
/// </summary>
public abstract class Message
{
    public Guid Id { get; init; }
    public Guid ChatId { get; init; }
    public Guid SenderId { get; init; }
    public DateTimeOffset Timestamp { get; init; }

    public abstract string Display();
}

public sealed class TextMessage : Message
{
    public string Content { get; init; } = string.Empty;
    public override string Display() => $"[{Timestamp:u}] (text) {SenderId}: {Content}";
}

public sealed class ImageMessage : Message
{
    public string Url { get; init; } = string.Empty;
    public string? Caption { get; init; }
    public override string Display() => $"[{Timestamp:u}] (image) {SenderId}: url={Url}{(string.IsNullOrWhiteSpace(Caption) ? string.Empty : $" caption=\"{Caption}\"")}";
}

public sealed class FileMessage : Message
{
    public string FileName { get; init; } = string.Empty;
    public string FileUrl { get; init; } = string.Empty;
    public long SizeBytes { get; init; }
    public override string Display() => $"[{Timestamp:u}] (file) {SenderId}: {FileName} ({SizeBytes / 1024.0:F1} KB) -> {FileUrl}";
}

