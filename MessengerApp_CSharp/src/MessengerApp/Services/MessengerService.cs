using MessengerApp.Models;

namespace MessengerApp.Services;

/// <summary>
/// Main application service to manage users, chats, and messaging.
/// </summary>
public class MessengerService
{
    private readonly Dictionary<Guid, User> _usersById = new();
    private readonly Dictionary<Guid, Chat> _chatsById = new();

    // User management
    public User RegisterUser(string name, bool isAdmin = false)
    {
        var id = Guid.NewGuid();
        User user = isAdmin ? new AdminUser(id, name) : new User(id, name);
        _usersById[id] = user;
        return user;
    }

    public void SetUserStatus(Guid userId, UserStatus status)
    {
        var user = RequireUser(userId);
        user.Status = status;
    }

    public User? GetUser(Guid userId) => _usersById.GetValueOrDefault(userId);

    public IReadOnlyList<User> FindUsersByName(string query)
    {
        var q = (query ?? string.Empty).Trim().ToLowerInvariant();
        return _usersById.Values
            .Where(u => u.Name.ToLowerInvariant().Contains(q))
            .ToList();
    }

    // Chat management
    public Chat CreateChat(IEnumerable<Guid> participantIds)
    {
        var ids = new HashSet<Guid>(participantIds ?? Array.Empty<Guid>());
        if (ids.Count < 2) throw new ArgumentException("A chat requires at least two participants.");
        foreach (var id in ids) RequireUser(id);
        var chat = new Chat(Guid.NewGuid(), ids);
        _chatsById[chat.Id] = chat;
        return chat;
    }

    public Chat? GetChat(Guid chatId) => _chatsById.GetValueOrDefault(chatId);

    // Messaging (polymorphic)
    public TextMessage SendText(Guid chatId, Guid senderId, string content)
    {
        var chat = RequireChat(chatId);
        RequireParticipant(chat, senderId);
        var msg = new TextMessage
        {
            Id = Guid.NewGuid(),
            ChatId = chatId,
            SenderId = senderId,
            Timestamp = DateTimeOffset.UtcNow,
            Content = content
        };
        chat.AddMessage(msg);
        return msg;
    }

    public ImageMessage SendImage(Guid chatId, Guid senderId, string url, string? caption = null)
    {
        var chat = RequireChat(chatId);
        RequireParticipant(chat, senderId);
        var msg = new ImageMessage
        {
            Id = Guid.NewGuid(),
            ChatId = chatId,
            SenderId = senderId,
            Timestamp = DateTimeOffset.UtcNow,
            Url = url,
            Caption = caption
        };
        chat.AddMessage(msg);
        return msg;
    }

    public FileMessage SendFile(Guid chatId, Guid senderId, string fileName, string fileUrl, long sizeBytes)
    {
        var chat = RequireChat(chatId);
        RequireParticipant(chat, senderId);
        var msg = new FileMessage
        {
            Id = Guid.NewGuid(),
            ChatId = chatId,
            SenderId = senderId,
            Timestamp = DateTimeOffset.UtcNow,
            FileName = fileName,
            FileUrl = fileUrl,
            SizeBytes = sizeBytes
        };
        chat.AddMessage(msg);
        return msg;
    }

    public IReadOnlyList<Message> ListMessages(Guid chatId)
    {
        var chat = RequireChat(chatId);
        return chat.GetMessages();
    }

    // Helpers
    private User RequireUser(Guid userId)
    {
        var user = GetUser(userId);
        return user ?? throw new KeyNotFoundException($"User not found: {userId}");
    }

    private Chat RequireChat(Guid chatId)
    {
        var chat = GetChat(chatId);
        return chat ?? throw new KeyNotFoundException($"Chat not found: {chatId}");
    }

    private static void RequireParticipant(Chat chat, Guid userId)
    {
        if (!chat.ParticipantIds.Contains(userId))
            throw new InvalidOperationException("User is not a participant of the chat.");
    }
}

