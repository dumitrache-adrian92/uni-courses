// utility site functions

/**
 * Called on a user's profile page to add it as friend.
 */
function addFriendProfile(userId) {
	// send ajax GET request to the server
	$.get("/inside/friends/add?id=" + userId, function(data) {
		// reload the page to see your new friends
		window.location.reload();
	});
}

/**
 * Function to approve a friendship request.
 *
 * The numeric ID of the user is required as parameter.
 */
function acceptFriend(friendId) {
	$.get("/inside/friends/accept?id=" + friendId, function(data) {
		// reload the page to see your new friends
		window.location.reload();
	});
}

/* On document load callback */
$(function() {
	// add action for the addImage post button
	$('#newPostForm .addImage').on("click", function(event) {
		event.preventDefault();
		$("#newPostForm .imageUpload").show();
	});

	// add action for the profile add friend button
	$('.profile-view .addFriend').on("click", function(event) {
		event.preventDefault();
		var userId = $('.profile-view').data('userId');
		addFriendProfile(userId);
	});

	// add action for the friend accept button
	$('.friends .acceptFriend').on("click", function(event) {
		event.preventDefault();
		acceptFriend($(this).data("friend-id"));
	});

	$('.messages-nuke-btn').on("click", function(event) {
		event.preventDefault();
		if (confirm("Are you sure you want to delete all messages from this user?")) {
			window.location = '/inside/message/nuke/' + $(this).data('friend-id');
		}
	});
});

