using MessengerApp.Models;
using MessengerApp.Services;

namespace MessengerApp;

public static class Program
{
    private static readonly MessengerService App = new();

    public static void Main()
    {
        Console.WriteLine("MessengerApp CLI (C#)\n");
        while (true)
        {
            PrintMenu();
            Console.Write("Select an option: ");
            var choice = (Console.ReadLine() ?? string.Empty).Trim();

            try
            {
                switch (choice)
                {
                    case "1":
                        RegisterUser();
                        break;
                    case "2":
                        ListUsers();
                        break;
                    case "3":
                        CreateChat();
                        break;
                    case "4":
                        SendText();
                        break;
                    case "5":
                        ShowMessages();
                        break;
                    case "6":
                        SetStatus();
                        break;
                    case "7":
                        SearchUsers();
                        break;
                    case "0":
                        Console.WriteLine("Goodbye!");
                        return;
                    default:
                        Console.WriteLine("Unknown option.\n");
                        break;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}\n");
            }
        }
    }

    private static void PrintMenu()
    {
        Console.WriteLine("1) Register user");
        Console.WriteLine("2) List users");
        Console.WriteLine("3) Create chat");
        Console.WriteLine("4) Send text message");
        Console.WriteLine("5) Show chat messages");
        Console.WriteLine("6) Set user status");
        Console.WriteLine("7) Search users");
        Console.WriteLine("0) Quit");
    }

    private static void RegisterUser()
    {
        Console.Write("Enter user name: ");
        var name = Console.ReadLine() ?? string.Empty;
        Console.Write("Is admin? (y/N): ");
        var isAdmin = string.Equals(Console.ReadLine(), "y", StringComparison.OrdinalIgnoreCase);
        var user = App.RegisterUser(name, isAdmin);
        var tag = user is AdminUser ? " [ADMIN]" : string.Empty;
        Console.WriteLine($"Registered: {user.Id} ({user.Name}){tag}\n");
    }

    private static void ListUsers()
    {
        var users = App.FindUsersByName(string.Empty);
        if (users.Count == 0)
        {
            Console.WriteLine("No users registered.\n");
            return;
        }
        foreach (var u in users)
        {
            Console.WriteLine($"- {u.Id}: {u.Name} [{u.Status}]");
        }
        Console.WriteLine();
    }

    private static void CreateChat()
    {
        Console.Write("Enter comma-separated user IDs: ");
        var raw = Console.ReadLine() ?? string.Empty;
        var ids = raw.Split(',', StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
            .Select(x => Guid.Parse(x));
        var chat = App.CreateChat(ids);
        Console.WriteLine($"Created chat: {chat.Id}\n");
    }

    private static void SendText()
    {
        Console.Write("Chat ID: ");
        var chatId = Guid.Parse(Console.ReadLine() ?? string.Empty);
        Console.Write("Sender user ID: ");
        var senderId = Guid.Parse(Console.ReadLine() ?? string.Empty);
        Console.Write("Text content: ");
        var content = Console.ReadLine() ?? string.Empty;
        var msg = App.SendText(chatId, senderId, content);
        Console.WriteLine($"Sent -> {msg.Display()}\n");
    }

    private static void ShowMessages()
    {
        Console.Write("Chat ID: ");
        var chatId = Guid.Parse(Console.ReadLine() ?? string.Empty);
        var messages = App.ListMessages(chatId);
        if (messages.Count == 0)
        {
            Console.WriteLine("No messages.\n");
            return;
        }
        foreach (var m in messages)
        {
            Console.WriteLine(m.Display());
        }
        Console.WriteLine();
    }

    private static void SetStatus()
    {
        Console.Write("User ID: ");
        var userId = Guid.Parse(Console.ReadLine() ?? string.Empty);
        Console.Write("Status (Online/Offline): ");
        var statusIn = (Console.ReadLine() ?? string.Empty).Trim();
        var status = string.Equals(statusIn, "Online", StringComparison.OrdinalIgnoreCase) ? UserStatus.Online : UserStatus.Offline;
        App.SetUserStatus(userId, status);
        Console.WriteLine("Updated.\n");
    }

    private static void SearchUsers()
    {
        Console.Write("Query: ");
        var q = Console.ReadLine() ?? string.Empty;
        var users = App.FindUsersByName(q);
        if (users.Count == 0)
        {
            Console.WriteLine("No matches.\n");
            return;
        }
        foreach (var u in users)
        {
            Console.WriteLine($"- {u.Id}: {u.Name} [{u.Status}]");
        }
        Console.WriteLine();
    }
}

