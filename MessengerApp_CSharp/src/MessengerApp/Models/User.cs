namespace MessengerApp.Models;

/// <summary>
/// Represents a basic user in the messenger system.
/// Demonstrates encapsulation via private fields and public properties.
/// </summary>
public class User
{
    private Guid _id;
    private string _name;
    private UserStatus _status;

    public Guid Id
    {
        get => _id;
        private set => _id = value;
    }

    public string Name
    {
        get => _name;
        set => _name = string.IsNullOrWhiteSpace(value) ? throw new ArgumentException("Name cannot be empty") : value.Trim();
    }

    public UserStatus Status
    {
        get => _status;
        set => _status = value;
    }

    public User(Guid id, string name)
    {
        Id = id;
        Name = name;
        Status = UserStatus.Offline;
    }

    public bool IsOnline() => Status == UserStatus.Online;
}

public enum UserStatus
{
    Online,
    Offline
}

/// <summary>
/// Specialized user with administrative capabilities (demonstrates inheritance).
/// </summary>
public sealed class AdminUser : User
{
    public AdminUser(Guid id, string name) : base(id, name) { }
}

