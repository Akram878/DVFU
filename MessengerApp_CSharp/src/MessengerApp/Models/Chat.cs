namespace MessengerApp.Models;

/// <summary>
/// Represents a conversation among two or more users.
/// </summary>
public class Chat
{
    public Guid Id { get; init; }
    public HashSet<Guid> ParticipantIds { get; } = new();
    private readonly List<Message> _messages = new();

    public Chat(Guid id, IEnumerable<Guid> participantIds)
    {
        if (participantIds is null) throw new ArgumentNullException(nameof(participantIds));
        var set = new HashSet<Guid>(participantIds);
        if (set.Count < 2) throw new ArgumentException("A chat requires at least two unique participants.");

        Id = id;
        foreach (var pid in set) ParticipantIds.Add(pid);
    }

    public IReadOnlyList<Message> GetMessages() => _messages.AsReadOnly();

    public void AddMessage(Message message)
    {
        if (!ParticipantIds.Contains(message.SenderId))
            throw new InvalidOperationException("Sender must be a chat participant.");
        _messages.Add(message);
    }
}

