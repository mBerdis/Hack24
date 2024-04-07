namespace CookBook.App.Messages;

public record TemplateEditMessage
{
    public required Guid TemplateId { get; init; }
}
